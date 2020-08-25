#ifndef EIGENALGEBRA_HPP
#define EIGENALGEBRA_HPP

#include <Eigen/Dense>
#include <boost/numeric/odeint/external/eigen/eigen_algebra.hpp>

namespace Algebra {
	template<typename _Scalar, Eigen::Index _size = Eigen::Dynamic>
	struct EigenAlgebra : public boost::numeric::odeint::vector_space_algebra{
		typedef _Scalar 														scalar;
		typedef Eigen::Matrix<scalar, _size, _size> 							matrix;
		typedef typename std::add_const<matrix>::type 							const_matrix;
		typedef Eigen::Ref<matrix> 												matrix_ref;
		typedef Eigen::Ref<const_matrix> 										const_matrix_ref;

		typedef Eigen::Matrix<scalar, _size, 1>									vector;
		typedef typename std::add_const<vector>::type 							const_vector;
		typedef Eigen::Ref<vector> 												vector_ref;
		typedef Eigen::Ref<const_vector> 										const_vector_ref;

		typedef Eigen::Matrix<scalar, 1, _size>									rowVector;
		typedef typename std::add_const<rowVector>::type 						const_rowVector;
		typedef Eigen::Ref<rowVector>											rowVector_ref;
		typedef Eigen::Ref<const_rowVector>										const_rowVector_ref;

		typedef Eigen::Index													size_type;

		static matrix ZeroMatrix(const size_type i, const size_type j) {
			return matrix::Zero( i, j );
		}

		static vector ZeroVector(const size_type i) {
			return vector::Zero( i );
		}

		static rowVector ZeroRowVector(const size_type i) {
			return rowVector::Zero( i );
		}

		template<typename T1>
		static auto softsign(const T1 & rhs) {
			return (rhs.array() / (abs(rhs).array() + 1)).matrix();
		}

		template<typename T>
		static auto norm_inf(const T & rhs) {
			return rhs.template lpNorm<Eigen::Infinity>();
		}
	};
}

#endif //EIGENALGEBRA_HPP