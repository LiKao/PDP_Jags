#include <Eigen/Dense>
#include <boost/numeric/odeint/external/eigen/eigen_algebra.hpp>

/* namespace std {
	template<typename Scalar, int i, int j>
	Eigen::Matrix<Scalar,i,j> abs(const Eigen::Matrix<Scalar,i,j> & m) {
		return m.cwiseAbs();
	}
} */

namespace Algebra {
	template<typename _Scalar>
	struct EigenAlgebra {
		typedef _Scalar 														Scalar_type;
		typedef Eigen::Matrix<Scalar_type, Eigen::Dynamic, Eigen::Dynamic> 		Matrix_type;
		typedef Eigen::Matrix<Scalar_type, Eigen::Dynamic, 1>					Vector_type;
		typedef Eigen::Matrix<Scalar_type, 1, Eigen::Dynamic>					RowVector_type;

		typedef Eigen::Index													size_type;

		static Matrix_type ZeroMatrix(const size_type i, const size_type j) {
			return Matrix_type::Zero( i, j );
		}

		static Vector_type ZeroVector(const size_type i) {
			return Vector_type::Zero( i );
		}

		static RowVector_type ZeroRowVector(const size_type i) {
			return RowVector_type::Zero( i );
		}

		static Matrix_type IdentityMatrix(const size_type i, const size_type j) {
			return Matrix_type::Identity( i, j );
		}

		static Matrix_type OnesMatrix(const size_type i, const size_type j) {
			return Matrix_type::Ones( i, j );
		}

		static Vector_type OnesVector(const size_type i) {
			return Vector_type::Ones( i );
		}

		static RowVector_type OnesRowVector(const size_type i) {
			return RowVector_type::Ones( i );
		}

		static Matrix_type ConstantMatrix(const size_type i, const size_type j, const Scalar_type & c) {
			return Matrix_type::Constant( i, j, c );
		}

		static Vector_type ConstantVector(const size_type i, const Scalar_type & c) {
			return Vector_type::Constant( i, c );
		}

		static RowVector_type ConstantRowVector(const size_type i, const Scalar_type & c) {
			return RowVector_type::Constant( i, c );
		}

		static Matrix_type RandomMatrix(const size_type i, const size_type j) {
			return Matrix_type::Random( i, j );
		}

		static Vector_type RandomVector(const size_type i) {
			return Vector_type::Random( i );
		}

		static RowVector_type RandomRowVector(const size_type i) {
			return RowVector_type::Random( i );
		}

		// Haddamard product for matrices and vectors
		template<typename T1, typename T2>
		static auto HProd(const T1 & lhs, const T2 & rhs){
			return lhs.cwiseProduct( rhs );
		}

		static Scalar_type norm_inf(const Matrix_type & m) {
			return m.template lpNorm<Eigen::Infinity>();
		}

		static Scalar_type norm_inf(const Vector_type & v) {
			return v.template lpNorm<Eigen::Infinity>();	
		}

		static Scalar_type norm_inf(const RowVector_type & v) {
			return v.template lpNorm<Eigen::Infinity>();	
		}
		
		static Scalar_type norm_inf(const Scalar_type & s) {
			return std::abs(s);
		}


		// For compatibility with boost::odeint

		template< class S1 , class Op >
	    static void for_each1( S1 &s1 , Op op )
	    {
	        // ToDo : build checks, that the +-*/ operators are well defined
	        op( s1 );
	    }

	    template< class S1 , class S2 , class Op >
	    static void for_each2( S1 &s1 , S2 &s2 , Op op )
	    {
	        op( s1 , s2 );
	    }

	    template< class S1 , class S2 , class S3 , class Op >
	    static void for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
	    {
	        op( s1 , s2 , s3 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class Op >
	    static void for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
	    static void for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
	    static void for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class Op >
	    static void for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class Op >
	    static void for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class Op >
	    static void for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class Op >
	    static void for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
	    static void for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
	    static void for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
	    static void for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
	    static void for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
	    static void for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 , s15 );
	    }
	};
}