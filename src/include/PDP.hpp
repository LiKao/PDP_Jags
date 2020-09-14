#ifndef PDP_HPP
#define PDP_HPP

#include <utility>
#include <cmath>
#include <type_traits>

#include <boost/numeric/odeint.hpp>

#include "config.h"

#include "EigenAlgebra.hpp"
#include "helpers/Assert.hpp"
#include "helpers/Memory.hpp"

namespace PDP {

	template<typename T>
	T tau(const T & v, const T & p) {
		return std::pow(v-T(0.5), p);
	}

	template<size_t nnodes, typename _Enable = void>
	struct simulator;

	class Network {
	public:
		typedef Algebra::EigenAlgebra						Algebra;
		typedef double										scalar;

		typedef Eigen::SparseMatrix<double>					matrix;
		typedef Eigen::VectorXd								vector;
		typedef Eigen::Index								size_type;

		typedef vector 										state_type;
		
		typedef boost::numeric::odeint::runge_kutta_dopri5<state_type, scalar, state_type, scalar, Algebra, Algebra>		ode_method;
		typedef boost::numeric::odeint::controlled_runge_kutta<ode_method> 													stepper_type;

		template<size_t nnodes, typename _Enable>
		friend struct simulator;

		Network(const size_type nnodes, const scalar _d=0.1) :
			m_w(nnodes, nnodes + 1), m_d(_d), m_nnodes( nnodes )
		{
			Assert(nnodes > 0, "Negative number of nodes in network", std::invalid_argument );
		}

		template<typename T1, typename T2>
		void ALWAYS_INLINE netin(const T1 & state, T2 & res) const noexcept {
			res.noalias() = w_normalized() * state;
			res += v_normalized();
		}


		template<typename T1, typename T2>
		void ALWAYS_INLINE delta_act(const T1 & state, T2 & dadt) const noexcept {
			netin( state, dadt );
			dadt -= (state.array() * (abs( dadt ).array() + 1)).matrix();
		}

		template<typename T1, typename T2>
		void ALWAYS_INLINE astar(const T1 & state, T2 & target) const noexcept {
			netin(state, target);
			target = (target.array() / (abs( target ).array() + 1)).matrix();
		}

		template<typename T>
		scalar ALWAYS_INLINE stress(const T & state) const noexcept {
			auto * buff = reinterpret_cast<double*>( aligned_alloca(sizeof(double)*nnodes(), EIGEN_DEFAULT_ALIGN_BYTES) );
			Eigen::Map<vector, EIGEN_DEFAULT_ALIGN_BYTES> target(buff, nnodes());
			astar(state, target);
			return ( target - state).template lpNorm<Eigen::Infinity>();
		}

		void link(size_type row, size_type column, scalar weight) {
			m_w.insert(row-1, column) = weight/d();
			//m_w(row-1, column-1) = weight/d();
		}

		void biLink(size_type row, size_type column, scalar weight) {
			link(row, column, weight);
			link(column, row, weight);
		}

		void input(size_type row, scalar weight) {
			m_w.insert(row-1,0) = weight/d();
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

		void simulate(Eigen::Ref<state_type> state, const scalar dt=1, const scalar max_t=150, const scalar tol=1.0e-05) noexcept;

		const matrix w_normalized() const { return m_w.rightCols(nnodes()); }
		const matrix v_normalized() const { return m_w.leftCols(1); }

		const matrix w() const {
			return w_normalized()*d();
		}

		const vector v() const {
			return v_normalized()*d();
		}

		const scalar & d()     const	{ return m_d; }

		size_type nnodes() const { return m_nnodes; }

	private:
		matrix m_w;
		//vector m_v;
		scalar m_d;
		size_type m_nnodes;
	};

}

#endif // PDP_HPP