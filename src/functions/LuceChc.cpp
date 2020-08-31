#include <util/dim.h>

#include "helpers/NetworkTemplate.hpp"
#include "helpers/MemoryBlock.hpp"
#include "helpers/RingPointer.hpp"

#include "include/EigenAlgebra.hpp"
#include "include/PDP.hpp"

#include "LuceChc.hpp"

namespace PDP {
	LuceChc::LuceChc() : ArrayFunction("LuceChc", 4) {}

	void LuceChc::evaluate(double *value,
			   	      		 std::vector<double const *> const &args,
            	             std::vector<std::vector<unsigned int> > const &dims ) const
	{
        const auto node1  = static_cast<Eigen::Index>( *args[0] ) - 1;
        const auto node2  = static_cast<Eigen::Index>( *args[1] ) - 1;
        const auto lambda = *args[2];
        const auto nnodes = dims[3][0];

        const auto outdim = product(dims[3].begin() + 1, dims[3].end());

        const Eigen::Map<const Eigen::ArrayXd> act(args[3], nnodes, outdim);
        auto * const buff1 = reinterpret_cast<double*>( alloca(sizeof(double)*outdim) );
        Eigen::Map<Eigen::VectorXd> act1pw(buff1, outdim);
        act1pw = (act.row(node1) * lambda).exp();

        auto * const buff2 = reinterpret_cast<double*>( alloca(sizeof(double)*outdim) );
        Eigen::Map<Eigen::VectorXd> act2pw(buff2, outdim);
        act2pw = (act.row(node2) * lambda).exp();

        Eigen::Map<Eigen::VectorXd> out(value, outdim);
        out = act1pw / (act1pw + act2pw);
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