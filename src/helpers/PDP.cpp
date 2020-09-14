#include "config.h"

#include "include/PDP.hpp"
#include "helpers/VecDispatcher.hpp"

#include <iostream>

namespace PDP {


	template<>
	struct simulator<0> {
		typedef Network::Algebra																				Algebra;
		typedef Network::scalar 																				scalar;
		typedef Network::vector 																				vector;
		typedef vector 																							deriv;
		typedef boost::numeric::odeint::initially_resizer														resizer;
		typedef boost::numeric::odeint::runge_kutta_dopri5<vector,scalar,deriv,scalar,Algebra,Algebra,resizer>			
				ode_method;
		typedef Algebra::error_checker<vector>																	error_checker;
		//typedef boost::numeric::odeint::default_error_checker<double,Algebra,Algebra>							error_checker;
		typedef boost::numeric::odeint::default_step_adjuster<scalar,scalar>									step_adjuster;
		typedef boost::numeric::odeint::controlled_runge_kutta<ode_method,error_checker,step_adjuster>			stepper_type;

		struct adapt {
			adapt(const Network & _net) : net(_net) {}

			ALWAYS_INLINE void operator()(const vector & state, deriv & dadt, scalar t) const noexcept
			{
				net.delta_act( state, dadt );
			}

			const Network & net;
		};

		struct terminate {
			terminate(const Network & _net, const scalar & _tol) : net(_net), tol(_tol), was_stressed(false) {}

			ALWAYS_INLINE bool operator()(const vector & state) noexcept
			{
				const auto stress = net.stress(state);
				was_stressed = was_stressed || ( stress > tol);
			 	return was_stressed && (stress < tol);
			}

			const Network & net;
			const scalar  & tol;
			bool was_stressed;
		};

		template<typename T>
		static /*ALWAYS_INLINE*/ void run ( T & state, const Network & net, const scalar dt, const scalar max_t, const scalar tol) noexcept
		{
			auto * buff = reinterpret_cast<double*>( aligned_alloca(sizeof(double)*net.nnodes(), EIGEN_DEFAULT_ALIGN_BYTES) );

			Eigen::Map<vector,EIGEN_DEFAULT_ALIGN_BYTES> fstate(buff, net.nnodes());
			fstate = state;
			//auto adapt = [&net](const auto & state, auto & dadt, double t ) { net.delta_act( state, dadt ); };
			//auto stepper = boost::numeric::odeint::make_controlled(tol, tol, Network::ode_method());
			auto stepper = stepper_type(error_checker(tol,tol), step_adjuster(), ode_method());
			auto ode_range = boost::numeric::odeint::make_adaptive_range(std::ref(stepper), adapt(net), fstate, 0, max_t*net.d(), dt*net.d());
			// If the initial stress is to low, we might terminate to early.
			// ensure that the network actually runs first, before we determine termination.
			//bool was_stressed = false;
			std::find_if( ode_range.first, ode_range.second, terminate( net, tol ) );
			state = fstate;
		}
	};


 	template<size_t nnodes>
	struct simulator<nnodes, typename std::enable_if<(nnodes <= (PDPMAXVECTORSIZE))>::type> {
		typedef Network::Algebra																				Algebra;
		typedef Network::scalar 																				scalar;
		typedef Eigen::Matrix<scalar, nnodes + 1, 1>															vector;
		typedef Eigen::Matrix<scalar, nnodes, nnodes + 1>														matrix;
		typedef vector																							deriv;
		typedef boost::numeric::odeint::never_resizer															resizer;
		typedef boost::numeric::odeint::runge_kutta_dopri5<vector,scalar,deriv,scalar,Algebra,Algebra,resizer>			
				ode_method;
		typedef Algebra::error_checker<vector>																	error_checker;
		//typedef boost::numeric::odeint::default_error_checker<double,Algebra,Algebra>							error_checker;
		typedef boost::numeric::odeint::default_step_adjuster<scalar,scalar>									step_adjuster;
		typedef boost::numeric::odeint::controlled_runge_kutta<ode_method,error_checker,step_adjuster>			stepper_type;

		struct adapt {
			adapt(const matrix & _w) 
			: w( _w )
			{}

			ALWAYS_INLINE void operator()(const vector & state, deriv & dadt, scalar t) const noexcept
			{
				//std::cout << "T: " << t << std::endl;
				dadt.template tail<nnodes>().noalias() = w * state;
				dadt.template tail<nnodes>() -= (state.template tail<nnodes>().array() * (abs( dadt.template tail<nnodes>() ).array() + 1)).matrix();
				dadt(0) = 0;
			}

			const matrix &	w;
		};

		struct terminate {
			terminate(const matrix & _w, const scalar & _tol) 
			: w(_w), tol(_tol), was_stressed(false) 
			{}

			scalar ALWAYS_INLINE stress(const vector & state) const noexcept {
				Eigen::Matrix<scalar, nnodes, 1> netin = w * state;
				auto target = (netin.array() / (abs( netin ).array() + 1)).matrix();
				return (target - state.template tail<nnodes>()).template lpNorm<Eigen::Infinity>();
			}


			ALWAYS_INLINE bool operator()(const vector & state) noexcept
			{
				const auto strs = stress(state);
				//std::cout << "Stress: " << strs << std::endl;
				was_stressed = was_stressed || ( strs > tol);
			 	return was_stressed && (strs < tol);
			}

			const matrix &	w;
			const scalar & tol;
			bool was_stressed;
		};

		template<typename T>
		static /*ALWAYS_INLINE*/ void run (T & state, const Network & net, const scalar dt, const scalar max_t, const scalar tol) noexcept
		{
			vector fstate;
			fstate.template tail<nnodes>() = state;
			fstate(0) = 1;
			const matrix w( net.m_w );

			//auto adapt = [&net](const auto & state, auto & dadt, double t ) { net.delta_act( state, dadt ); };
			auto stepper = stepper_type(error_checker(tol,tol), step_adjuster(), ode_method());
			//auto stepper = boost::numeric::odeint::make_controlled(tol, tol, ode_method() );
			auto ode_range = boost::numeric::odeint::make_adaptive_range(std::ref(stepper), adapt(w), fstate, 0, max_t*net.d(), dt*net.d());
			// If the initial stress is to low, we might terminate to early.
			// ensure that the network actually runs first, before we determine termination.
			//bool was_stressed = false;
			std::find_if( ode_range.first, ode_range.second, terminate( w, tol ) );
			state = fstate.template tail<nnodes>();
		}
	};

	template<size_t nnodes>
	struct simulator<nnodes, typename std::enable_if<(nnodes > (PDPMAXVECTORSIZE))>::type> : public simulator<0> {};

	// Workaround for bug with template template parameters in CLANG
	template<size_t nnodes> 
	struct simulator_wrapper : public simulator<nnodes> {};

	void Network::simulate(Eigen::Ref<state_type> state, const scalar dt, const scalar max_t, const scalar tol) noexcept
 	{
 		//m_w.makeCompressed();  
		//simulator<1>::run( state, *this, dt, max_t, tol );
		#ifdef PDPDONTVECTORIZE
			simulator<0>::run( state, *this, dt, max_t, tol );
		#else
			if(nnodes() > PDPMAXVECTORSIZE) {
				simulator<0>::run( state, *this, dt, max_t, tol );
			}
			else {
				dispatcher<simulator_wrapper, static_log2<PDPMAXVECTORSIZE>::value >::call( nnodes(), state, *this, dt, max_t, tol );
			}
		#endif
	}

}