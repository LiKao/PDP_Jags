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

		static matrix IdentityMatrix(const size_type i, const size_type j) {
			return matrix::Identity( i, j );
		}

		static matrix OnesMatrix(const size_type i, const size_type j) {
			return matrix::Ones( i, j );
		}

		static vector OnesVector(const size_type i) {
			return vector::Ones( i );
		}

		static rowVector OnesRowVector(const size_type i) {
			return rowVector::Ones( i );
		}

		static matrix ConstantMatrix(const size_type i, const size_type j, const scalar & c) {
			return matrix::Constant( i, j, c );
		}

		static vector ConstantVector(const size_type i, const scalar & c) {
			return vector::Constant( i, c );
		}

		static rowVector ConstantRowVector(const size_type i, const scalar & c) {
			return rowVector::Constant( i, c );
		}

		static matrix RandomMatrix(const size_type i, const size_type j) {
			return matrix::Random( i, j );
		}

		static vector RandomVector(const size_type i) {
			return vector::Random( i );
		}

		static rowVector RandomRowVector(const size_type i) {
			return rowVector::Random( i );
		}

		template<typename M>
		static auto addScalar(const M & m, scalar s) {
			return (m.array() + s).matrix();
		}

		template<typename M>
		static auto noalias(M & m) {
			return m.noalias();
		}

		// Haddamard product for matrices and vectors
		template<typename T1, typename T2>
		static auto HProd(const T1 & lhs, const T2 & rhs){
			return lhs.cwiseProduct( rhs );
		}

		// Haddamard division
		template<typename T1, typename T2>
		static auto HDiv(const T1 & lhs, const T2 & rhs) {
			return ( lhs.array()/rhs.array() ).matrix();
		}

		template<typename T1>
		static auto softsign(const T1 & rhs) {
			return HDiv( rhs, addScalar( abs(rhs), 1 ) );
		}

		template<typename T>
		static auto norm_inf(const T & rhs) {
			return rhs.template lpNorm<Eigen::Infinity>();
		}
	};
}

