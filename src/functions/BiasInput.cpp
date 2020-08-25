#include <util/dim.h>

#include "helpers/NetworkTemplate.hpp"

#include "BiasInput.hpp"

#include <iostream>

namespace PDP {

	BiasInput::BiasInput() : jags::ArrayFunction("BiasInput", 3) {}

	void BiasInput::evaluate( double *value,
							  std::vector<double const *> const &args,
        					  std::vector<std::vector<unsigned int> > const &dims ) const
	{
		const auto innets = MakeNetworkTemplate( args[2], dims[2][0] );
        auto outnets = MakeNetworkTemplate( value, dim(dims, args)[0], innets );
        const auto pram = *args[0];
        const auto node = *args[1];
        outnets.entries().emplace_back( node, 0.0, pram );
	}

	bool BiasInput::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
		return 
			(dims[0].size() == 1) && (dims[0][0] == 1) && 		// Single dim parameters index
			(dims[2].size() == 1) && (dims[0][0] == 1) &&		// Single node index
            (dims[2].size() == 1) &&
			(dims[2][0] >= NetworkTemplate<double>::s_header_length);		// Network must have at least a header
			
	}

    bool BiasInput::checkParameterValue( std::vector<double const *> const &args,
        	                             std::vector<std::vector<unsigned int> > const &dims) const
    {
    	return (*args[0] >= 1) && (*args[1] >= 1);
    }

    bool BiasInput::checkParameterDiscrete(std::vector<bool> const &mask) const 
    {
    	return mask[0] && mask[1];
    }

    std::vector<unsigned int> 
    BiasInput::dim(std::vector <std::vector<unsigned int> > const &dims,
                         std::vector <double const *> const &values) const
    {   
        const auto innet = MakeNetworkTemplate( values[2], dims[2][0] );
        return { innet.extend( 1 ) };
    }

    bool BiasInput::checkParameterFixed(std::vector<bool> const &mask) const {
        return mask[0] && mask[1] && mask[2];
    }
}
	