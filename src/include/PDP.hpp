#include <utility>
#include <cmath>

#include <boost/numeric/odeint.hpp>

namespace PDP {

	template<typename T>
	T tau(const T & v, const T & p) {
		return std::pow(v-T(0.5), p);
	}

	template<typename _Algebra>
	class Network {
	public:
		typedef _Algebra 							Algebra;
		typedef typename Algebra::Scalar_type		Scalar_type;
		typedef typename Algebra::Matrix_type		Matrix_type;
		typedef typename Algebra::Vector_type		Vector_type;
		typedef typename Algebra::RowVector_type	RowVector_type;
		typedef typename Algebra::size_type			size_type;

		typedef Vector_type 						state_type;
		
		typedef boost::numeric::odeint::runge_kutta_cash_karp54<state_type, Scalar_type, state_type, Scalar_type, Algebra>		ode_method;
		typedef boost::numeric::odeint::controlled_runge_kutta<ode_method> 														stepper_type;

		Network(const Matrix_type & _w, const Vector_type & _v, const Scalar_type _d=0.1) :
			m_w(), m_v(), m_d(_d)
		{
			m_w = _w/d();
			m_v = _v/d();
		}

		auto netin(const state_type & state) const {
			return w_normalized() * state + v_normalized();
		}

		state_type delta_act(const state_type & state) const {
			const auto ni = netin( state );
			return ni - Algebra::HProd( state, Algebra::OnesVector( nnodes() ) +  abs( Vector_type( ni ) ) );
		}


		std::vector<std::pair<Scalar_type,state_type>>
		simulate(const state_type & init, const Scalar_type & dt=1, const Scalar_type & max_t=150) const {
			std::vector<std::pair<Scalar_type,state_type>> nrv;
			state_type state = init;
			auto adapt = [this](const state_type & state, state_type & dadt, double t ) {
				dadt = delta_act( state );
			};
			auto observer = [&nrv,this](const state_type &act , double t) { nrv.push_back(std::make_pair(t/d(),act)); };
			boost::numeric::odeint::integrate_const( stepper_type(), adapt, state, 0.0, max_t*d(), dt*d(), observer );
			return nrv;
		}

		      Matrix_type & w_normalized()       { return m_w; }
		const Matrix_type & w_normalized() const { return m_w; }
		      Vector_type & v_normalized()       { return m_v; }
		const Vector_type & v_normalized() const { return m_v; }

		const Matrix_type w() const {
			return m_w*d();
		}

		const Vector_type v() const {
			return m_v*d();
		}

		const Scalar_type & d()     const	{ return m_d; }

		size_type nnodes() const { return v().size(); }

	private:
		Matrix_type m_w;
		Vector_type m_v;
		Scalar_type m_d;
	};

}