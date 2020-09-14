#include <util/dim.h>

#include "helpers/NetworkTemplate.hpp"
#include "helpers/MemoryBlock.hpp"
#include "helpers/RingPointer.hpp"
#include "helpers/Memory.hpp"
#include "helpers/VecDispatcher.hpp"

#include "include/EigenAlgebra.hpp"
#include "include/PDP.hpp"


#include "LuceChc.hpp"

namespace PDP {
    namespace {
        template<typename T, size_t degree, size_t i = 0>
        struct fast_approx_exp {
            typedef T                           value_type;
            typedef typename T::value_type      scalar_type;

            template<typename U>
            static void ALWAYS_INLINE evaluate(const U inp, value_type & res) {
                fast_approx_exp<T, degree, i + 1>::evaluate(inp, res);
                res = res * res;
            }
        };

        template<typename T, size_t degree>
        struct fast_approx_exp<T,degree,degree> {
            typedef T                           value_type;
            typedef typename T::value_type      scalar_type;

            template<typename U>
            static void ALWAYS_INLINE evaluate(const U inp, value_type & res) {
                constexpr scalar_type c = 1.0 / static_cast<scalar_type>(1u << degree);
                res = 1.0 + c * inp;
            }
        };

        template<size_t N, typename _Enable = void>
        struct LuceChcEval;

        template<>
        struct LuceChcEval<0> {
            typedef double                                                                  scalar_type;
            typedef Eigen::Array<scalar_type,Eigen::Dynamic,1>                              avec;
            typedef Eigen::Array<scalar_type,Eigen::Dynamic,Eigen::Dynamic>                 amat;
            typedef Eigen::Map<avec, EIGEN_DEFAULT_ALIGN_BYTES>                             local_vec;

            static void run( double *value,  const Eigen::Index node1, const Eigen::Index node2, 
                             const Eigen::Index nnodes, const double lambda, const long int outdim,
                             const double * act) 
            {
                const Eigen::Map<const amat> actm(act, nnodes, outdim);

                auto * const buff1 = reinterpret_cast<double*>( aligned_alloca(sizeof(double)*outdim, EIGEN_DEFAULT_ALIGN_BYTES) );
                local_vec act1pw(buff1, outdim);
                fast_approx_exp<local_vec,6>::evaluate(actm.row(node1) * lambda, act1pw);

                auto * const buff2 = reinterpret_cast<double*>( aligned_alloca(sizeof(double)*outdim, EIGEN_DEFAULT_ALIGN_BYTES) );
                local_vec act2pw(buff2, outdim);
                fast_approx_exp<local_vec,6>::evaluate(actm.row(node2) * lambda, act2pw);

                Eigen::Map<avec> out(value, outdim);
                out = act1pw / (act1pw + act2pw);
            }
        };

        template<size_t N>
        struct LuceChcEval<N, typename std::enable_if<(N <= (LUCEMAXVECTORSIZE))>::type>
        {
            typedef double                                                                  scalar_type;
            typedef Eigen::Array<scalar_type,N,1>                                           avec;
            typedef Eigen::Array<scalar_type,Eigen::Dynamic,N>                              amat;
            typedef avec                                                                    local_vec;


            static void run( double *value,  const Eigen::Index node1, const Eigen::Index node2, 
                             const Eigen::Index nnodes, const double lambda, const long int outdim,
                             const double * act) 
            {
                const Eigen::Map<const amat> actm(act, nnodes, outdim);

                local_vec act1pw;
                fast_approx_exp<local_vec,6>::evaluate(actm.row(node1) * lambda, act1pw);

                local_vec act2pw;
                fast_approx_exp<local_vec,6>::evaluate(actm.row(node2) * lambda, act2pw);

                Eigen::Map<local_vec> out(value, outdim);
                out = act1pw / (act1pw + act2pw);
            }

        };

        template<size_t N>
        struct LuceChcEval<N, typename std::enable_if<(N > (LUCEMAXVECTORSIZE))>::type> : public LuceChcEval<0> {};

        template<size_t N>
        struct LuceChcEval_wrapper : public LuceChcEval<N> {};

    }

	LuceChc::LuceChc() : ArrayFunction("LuceChc", 4) {}

	void LuceChc::evaluate(double *value,
			   	      		 std::vector<double const *> const &args,
            	             std::vector<std::vector<unsigned int> > const &dims ) const
	{
        const auto node1  = static_cast<Eigen::Index>( *args[0] ) - 1;
        const auto node2  = static_cast<Eigen::Index>( *args[1] ) - 1;
        const auto lambda = *args[2];
        const auto nnodes = static_cast<Eigen::Index>( dims[3][0] );

        const auto outdim = product(dims[3].begin() + 1, dims[3].end());
        #ifdef PDPDONTVECTORIZE
            LuceChcEval<0>::run(value, node1, node2, nnodes, lambda, outdim, args[3]);
        #else
            if(outdim > LUCEMAXVECTORSIZE) {
                LuceChcEval<0>::run(value, node1, node2, nnodes, lambda, outdim, args[3]);
            }
            else {
                dispatcher<LuceChcEval_wrapper, static_log2<LUCEMAXVECTORSIZE>::value>::call( outdim, value, node1, node2, nnodes, lambda, outdim, args[3] );
            }
        #endif
	}

	bool LuceChc::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
    {
        return 
            (dims[0].size() == 1) && (dims[0][0] == 1) &&
            (dims[1].size() == 1) && (dims[1][0] == 1) &&
            (dims[2].size() == 1) && (dims[2][0] == 1);

	}

    bool LuceChc::checkParameterValue(std::vector<double const *> const &args,
        	                              std::vector<std::vector<unsigned int> > const &dims) const
    {
    	const auto nnodes = dims[3][0];
        return 
            (*args[0] >= 1) && (*args[0] <= nnodes) &&
            (*args[1] >= 1) && (*args[1] <= nnodes);
    }

    bool LuceChc::checkParameterFixed(std::vector<bool> const &mask) const {
        return mask[0] && mask[1];
    }
  
    std::vector<unsigned int> 
    LuceChc::dim(std::vector <std::vector<unsigned int> > const &dims,
            		 std::vector <double const *> const &values) const
    {
        const std::vector<unsigned int> nrv(dims[3].begin() + 1, dims[3].end());
        return jags::drop( nrv );
    }
}