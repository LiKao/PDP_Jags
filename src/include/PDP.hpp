#include <utility>
#include <cmath>

#include <boost/numeric/odeint.hpp>
#include "EigenAlgebra.hpp"
#include "helpers/Assert.hpp"

namespace PDP {

	template<typename T>
	T tau(const T & v, const T & p) {
		return std::pow(v-T(0.5), p);
	}

	template<Eigen::Index _size = Eigen::Dynamic>
	class Network {
	public:
		typedef Algebra::EigenAlgebra<double,_size>			Algebra;
		typedef typename Algebra::scalar					scalar;

		typedef typename Algebra::matrix					matrix;
		typedef typename Algebra::const_matrix   			const_matrix;
		typedef typename Algebra::matrix_ref 				matrix_ref;
		typedef typename Algebra::const_matrix_ref 			const_matrix_ref;

		typedef typename Algebra::vector					vector;
		typedef typename Algebra::const_vector 				const_vector;
		typedef typename Algebra::vector_ref 				vector_ref;
		typedef typename Algebra::const_vector_ref			const_vector_ref;


		typedef typename Algebra::size_type					size_type;

		typedef vector 										state_type;
		typedef vector_ref                          		state_ref;
		typedef const_vector_ref 							const_state_ref;
		
		typedef boost::numeric::odeint::runge_kutta_dopri5<state_type, scalar, state_type, scalar, Algebra>		ode_method;
		typedef boost::numeric::odeint::controlled_runge_kutta<ode_method> 										stepper_type;

		Network(const size_type nnodes = _size, const scalar _d=0.1) :
			m_w(), m_v(), m_d(_d)
		{
			Assert((_size == Eigen::Dynamic) || (_size == nnodes), "Size of constant network does not match", std::invalid_argument );
			Assert(nnodes > 0, "Negative number of nodes in network", std::invalid_argument );
			m_w = matrix::Zero( nnodes, nnodes );
			m_v = vector::Zero( nnodes );
		}

		template<typename T1, typename T2>
		void netin(const T1 & state, T2 & res) const {
			res.noalias() = w_normalized() * state + v_normalized();
		}

		template<typename T1, typename T2>
		void delta_act(const T1 & state, T2 & dadt) const {
			netin( state, dadt );
			dadt -= (state.array() * (abs( dadt ).array() + 1)).matrix();
		}

		template<typename T1, typename T2>
		void astar(const T1 & state, T2 & res) const {
			netin(state, res);
			res = Algebra::softsign( res );
		}

		template<typename T1>
		scalar stress(const T1 & state) const {
			state_type target;
			astar(state, target);
			return (target - state).template lpNorm<Eigen::Infinity>();
		}

		void link(size_type row, size_type column, scalar weight) {
			m_w(row-1, column-1) = weight/d();
		}

		void biLink(size_type row, size_type column, scalar weight) {
			link(row, column, weight);
			link(column, row, weight);
		}

		void input(size_type row, scalar weight) {
			m_v(row-1) = weight/d();
		}


		// TODO: In the current form, simulate methods only take state_type arguments
		// Generic templated forms would take other arguments, which may be more efficient
		// in terms of memory management. However, some Eigen types (e.g. Eigen::Map<>) seem to
		// incorrectly handle memory allocations when returned from an odeint::iterator and therefore
		// lead to segfaults. Therefore, we only take state_type forcing dynamic memory management
		// here to avoid crashes.
		template<typename Observer>
		void simulate(state_type & state, Observer observer, const scalar dt=1, const scalar max_t=150) const {
			auto adapt = [this](const auto & state, auto & dadt, scalar t ) { delta_act( state, dadt ); };
			auto oadapt = [this,&observer](const auto & act , scalar t){ observer(act, t/d()); };
			boost::numeric::odeint::integrate_const( stepper_type(), adapt, state, 0.0, max_t*d(), dt*d(), oadapt );
		}

		void simulate(state_type & state, const scalar dt=1, const scalar max_t=150, const scalar tol=1.0e-05) {
			auto adapt = [this](const auto & state, auto & dadt, double t ) { delta_act( state, dadt ); };
			auto stepper = boost::numeric::odeint::make_controlled(tol, tol, ode_method());
			auto ode_range = boost::numeric::odeint::make_adaptive_time_range(std::ref(stepper), adapt, state, 0, max_t*d(), dt*d());
			// If the initial stress is to low, we might terminate to early.
			// ensure that the network actually runs first, before we determine termination.
			bool was_stressed = false;
			std::find_if( ode_range.first, ode_range.second, [&tol,&was_stressed, this](const auto & state){ 
			 	was_stressed = was_stressed || (stress(state.first) > tol);
			 	return was_stressed && (stress(state.first) < tol);
			} );
		}

		      matrix & w_normalized()       { return m_w; }
		const matrix & w_normalized() const { return m_w; }
		      vector & v_normalized()       { return m_v; }
		const vector & v_normalized() const { return m_v; }

		const matrix w() const {
			return m_w*d();
		}

		const vector v() const {
			return m_v*d();
		}

		const scalar & d()     const	{ return m_d; }

		size_type nnodes() const { return v_normalized().size(); }

	private:
		matrix m_w;
		vector m_v;
		scalar m_d;
	};

}