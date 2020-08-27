#ifndef EIGENALGEBRA_HPP
#define EIGENALGEBRA_HPP

#include <Eigen/Dense>
#include <Eigen/Sparse>

#include <boost/numeric/odeint/external/eigen/eigen_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>

#include "config.h"

namespace Algebra {
	struct EigenAlgebra : public boost::numeric::odeint::default_operations 
	{

		template< class S1 , class Op >
	    static void ALWAYS_INLINE for_each1( S1 &s1 , Op op )
	    {
	        // ToDo : build checks, that the +-*/ operators are well defined
	        op( s1 );
	    }

	    template< class S1 , class S2 , class Op >
	    static void ALWAYS_INLINE for_each2( S1 &s1 , S2 &s2 , Op op )
	    {
	        op( s1 , s2 );
	    }

	    template< class S1 , class S2 , class S3 , class Op >
	    static void ALWAYS_INLINE for_each3( S1 &s1 , S2 &s2 , S3 &s3 , Op op )
	    {
	        op( s1 , s2 , s3 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class Op >
	    static void ALWAYS_INLINE for_each4( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class Op >
	    static void ALWAYS_INLINE for_each5( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 , class Op >
	    static void ALWAYS_INLINE for_each6( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class Op >
	    static void ALWAYS_INLINE for_each7( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class Op >
	    static void ALWAYS_INLINE for_each8( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class Op >
	    static void ALWAYS_INLINE for_each9( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class Op >
	    static void ALWAYS_INLINE for_each10( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class Op >
	    static void ALWAYS_INLINE for_each11( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class Op >
	    static void ALWAYS_INLINE for_each12( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class Op >
	    static void ALWAYS_INLINE for_each13( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class Op >
	    static void ALWAYS_INLINE for_each14( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 );
	    }

	    template< class S1 , class S2 , class S3 , class S4 , class S5 , class S6 ,class S7 , class S8 , class S9 , class S10 , class S11 , class S12 , class S13 , class S14 , class S15 , class Op >
	    static void ALWAYS_INLINE for_each15( S1 &s1 , S2 &s2 , S3 &s3 , S4 &s4 , S5 &s5 , S6 &s6 , S7 &s7 , S8 &s8 , S9 &s9 , S10 &s10 , S11 &s11 , S12 &s12 , S13 &s13 , S14 &s14 , S15 &s15 , Op op )
	    {
	        op( s1 , s2 , s3 , s4 , s5 , s6 , s7 , s8 , s9 , s10 , s11 , s12 , s13 , s14 , s15 );
	    }


		template<typename T>
		static ALWAYS_INLINE auto norm_inf(const T & rhs) {
			return rhs.template lpNorm<Eigen::Infinity>();
		}

		template< class Fac1 = double >
		struct scale_sum1
		{
		    const Fac1 m_alpha1;

		    scale_sum1( Fac1 alpha1 ) : m_alpha1( alpha1 ) { }

		    template< class T1 , class T2 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 ) const
		    {
		        t1.noalias() = m_alpha1 * t2;
		    }

		    typedef void result_type;
		};

		template< class Fac1 = double , class Fac2 = Fac1 >
		struct scale_sum2
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;

		    scale_sum2( Fac1 alpha1 , Fac2 alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

		    template< class T1 , class T2 , class T3 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3;
		    }

		    typedef void result_type;
		};


		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 >
		struct scale_sum3
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;

		    scale_sum3( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }

		    template< class T1 , class T2 , class T3 , class T4 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 ) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4;
		    }

		    typedef void result_type;
		};


		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 >
		struct scale_sum4
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;

		    scale_sum4( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) { }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5;
		    }

		    typedef void result_type;
		};


		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 >
		struct scale_sum5
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;
		    const Fac5 m_alpha5;

		    scale_sum5( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 , Fac5 alpha5 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6;
		    }

		    typedef void result_type;
		};


		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 >
		struct scale_sum6
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;
		    const Fac5 m_alpha5;
		    const Fac6 m_alpha6;

		    scale_sum6( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 , Fac5 alpha5 , Fac6 alpha6 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ){ }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 ,const T7 &t7) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7;
		    }

		    typedef void result_type;
		};


		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 >
		struct scale_sum7
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;
		    const Fac5 m_alpha5;
		    const Fac6 m_alpha6;
		    const Fac7 m_alpha7;

		    scale_sum7( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
		            Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) { }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 ) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8;
		    }

		    typedef void result_type;
		};


		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 >
		struct scale_sum8
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;
		    const Fac5 m_alpha5;
		    const Fac6 m_alpha6;
		    const Fac7 m_alpha7;
		    const Fac8 m_alpha8;

		    scale_sum8( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
		            Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) { }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 ) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9;
		    }

		    typedef void result_type;
		};

		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 >
		struct scale_sum9
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;
		    const Fac5 m_alpha5;
		    const Fac6 m_alpha6;
		    const Fac7 m_alpha7;
		    const Fac8 m_alpha8;
		    const Fac9 m_alpha9;

		    scale_sum9( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
		            Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) { }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 ) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10;
		    }

		    typedef void result_type;
		};

		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 , class Fac10 = Fac9 >
		struct scale_sum10
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;
		    const Fac5 m_alpha5;
		    const Fac6 m_alpha6;
		    const Fac7 m_alpha7;
		    const Fac8 m_alpha8;
		    const Fac9 m_alpha9;
		    const Fac10 m_alpha10;

		    scale_sum10( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
		            Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 , Fac10 alpha10 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) { }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 ) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11;
		    }

		    typedef void result_type;
		};


		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 , class Fac10 = Fac9 , class Fac11 = Fac10 >
		struct scale_sum11
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;
		    const Fac5 m_alpha5;
		    const Fac6 m_alpha6;
		    const Fac7 m_alpha7;
		    const Fac8 m_alpha8;
		    const Fac9 m_alpha9;
		    const Fac10 m_alpha10;
		    const Fac11 m_alpha11;

		    scale_sum11( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
		            Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
		            Fac10 alpha10 , Fac11 alpha11 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) { }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 ) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12;
		    }

		    typedef void result_type;
		};

		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 , class Fac10 = Fac9 , class Fac11 = Fac10 , class Fac12 = Fac11 >
		struct scale_sum12
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;
		    const Fac5 m_alpha5;
		    const Fac6 m_alpha6;
		    const Fac7 m_alpha7;
		    const Fac8 m_alpha8;
		    const Fac9 m_alpha9;
		    const Fac10 m_alpha10;
		    const Fac11 m_alpha11;
		    const Fac12 m_alpha12;

		    scale_sum12( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
		            Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
		            Fac10 alpha10 , Fac11 alpha11 , Fac12 alpha12 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) , m_alpha12( alpha12 ) { }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 , const T13 &t13 ) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12 + m_alpha12 * t13;
		    }

		    typedef void result_type;
		};

		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 , class Fac10 = Fac9 , class Fac11 = Fac10 , class Fac12 = Fac11 , class Fac13 = Fac12 >
		struct scale_sum13
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;
		    const Fac5 m_alpha5;
		    const Fac6 m_alpha6;
		    const Fac7 m_alpha7;
		    const Fac8 m_alpha8;
		    const Fac9 m_alpha9;
		    const Fac10 m_alpha10;
		    const Fac11 m_alpha11;
		    const Fac12 m_alpha12;
		    const Fac13 m_alpha13;

		    scale_sum13( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
		            Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
		            Fac10 alpha10 , Fac11 alpha11 , Fac12 alpha12 , Fac13 alpha13 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) , m_alpha12( alpha12 ) , m_alpha13( alpha13 ) { }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 , const T13 &t13 , const T14 &t14 ) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12 + m_alpha12 * t13 + m_alpha13 * t14;
		    }

		    typedef void result_type;
		};

		template< class Fac1 = double , class Fac2 = Fac1 , class Fac3 = Fac2 , class Fac4 = Fac3 , class Fac5 = Fac4 , class Fac6 = Fac5 , class Fac7 = Fac6 , class Fac8 = Fac7 , class Fac9 = Fac8 , class Fac10 = Fac9 , class Fac11 = Fac10 , class Fac12 = Fac11 , class Fac13 = Fac12 , class Fac14 = Fac13 >
		struct scale_sum14
		{
		    const Fac1 m_alpha1;
		    const Fac2 m_alpha2;
		    const Fac3 m_alpha3;
		    const Fac4 m_alpha4;
		    const Fac5 m_alpha5;
		    const Fac6 m_alpha6;
		    const Fac7 m_alpha7;
		    const Fac8 m_alpha8;
		    const Fac9 m_alpha9;
		    const Fac10 m_alpha10;
		    const Fac11 m_alpha11;
		    const Fac12 m_alpha12;
		    const Fac13 m_alpha13;
		    const Fac14 m_alpha14;

		    scale_sum14( Fac1 alpha1 , Fac2 alpha2 , Fac3 alpha3 , Fac4 alpha4 ,
		            Fac5 alpha5 , Fac6 alpha6 , Fac7 alpha7 , Fac8 alpha8 , Fac9 alpha9 ,
		            Fac10 alpha10 , Fac11 alpha11 , Fac12 alpha12 , Fac13 alpha13 , Fac14 alpha14 )
		    : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) , m_alpha6( alpha6 ) , m_alpha7( alpha7 ) , m_alpha8( alpha8 ) , m_alpha9( alpha9 ) , m_alpha10( alpha10 ) , m_alpha11( alpha11 ) , m_alpha12( alpha12 ) , m_alpha13( alpha13 ) , m_alpha14( alpha14 ) { }

		    template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6 , class T7 , class T8 , class T9 , class T10 , class T11 , class T12 , class T13 , class T14 , class T15 >
		    ALWAYS_INLINE void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 , const T7 &t7 , const T8 &t8 , const T9 &t9 , const T10 &t10 , const T11 &t11 , const T12 &t12 , const T13 &t13 , const T14 &t14 , const T15 &t15 ) const
		    {
		        t1.noalias() = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6 + m_alpha6 * t7 + m_alpha7 * t8 + m_alpha8 * t9 + m_alpha9 * t10 + m_alpha10 * t11 + m_alpha11 * t12 + m_alpha12 * t13 + m_alpha13 * t14 + m_alpha14 * t15;
		    }

		    typedef void result_type;
		};

	};
}

#endif //EIGENALGEBRA_HPP