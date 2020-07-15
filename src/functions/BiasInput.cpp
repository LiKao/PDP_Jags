#include <util/dim.h>

#include "helpers/JagsArray.hpp"

#include "BiasInput.hpp"

namespace PDP {
	BiasInput::BiasInput() : ArrayFunction("BiasInput", 3) {}

	void BiasInput::evaluate(double *value,
			   	      	std::vector<double const *> const &args,
            	        std::vector<std::vector<unsigned int> > const &dims ) const
	{
		auto nrv = JagsArray( value, dim(dims, args) );
		unsigned int pos(*args[0]);
		auto weight = JagsArray( args[1], dims[1] );
		auto net = JagsArray( args[2], dims[2] );
		nrv.copy( net );
		nrv.for_each( weight, [pos,&dims](auto trg, auto w){ trg[dims[2][1]][pos] = w; }, nrv.depth() - 2 - weight.depth() );
	}

	bool BiasInput::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
		// if we have an array of values
		if(dims[1].size() != 1 || dims[1][0] != 1) {
			// sizes must match, or we can't create the matrix
			for(size_t i = 0; i < std::min(dims[2].size() - 2, dims[1].size()); ++i) {
				if(dims[1][i] != dims[2][i+2]) {
					return false;
				}
			}
		}

		return (dims[0].size() == 1) && (dims[0][0] == 1) &&
			   (dims[2].size() >= 2) && (dims[2][0] + 1 == dims[2][1]);
	}

    bool BiasInput::checkParameterValue(std::vector<double const *> const &args,
        	                              std::vector<std::vector<unsigned int> > const &dims) const
    {

    	return (*args[0] >= 1) && (*args[0] <= dims[2][0]);

    }

    bool BiasInput::checkParameterDiscrete(std::vector<bool> const &mask) const 
    {
    	return mask[0];
    }
    
    std::vector<unsigned int> 
    BiasInput::dim(std::vector <std::vector<unsigned int> > const &dims,
            		 std::vector <double const *> const &values) const
    {
    	// If we have a single input, the dimensions are defined by the networks
    	if((dims[1].size() == 1) && (dims[1][0] == 1)) 
    		return dims[2];

    	// We need to identify which object has more dimensions
    	if(dims[1].size() + 2 <= dims[2].size())
    		return dims[2]; // Network is more complete

    	// We don't yet have multiple networks, so we create them
		std::vector<unsigned int> nrv{dims[2][0], dims[2][1]}; // First two dimensions are given by network structure
		nrv.insert(std::end(nrv),std::begin(dims[1]),std::end(dims[1])); // Take the rest from the parameter
		return jags::drop(nrv);
    }

}
	