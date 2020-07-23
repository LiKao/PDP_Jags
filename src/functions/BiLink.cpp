#include <util/dim.h>

#include "helpers/JagsArray.hpp"

#include "BiLink.hpp"

namespace PDP {
	BiLink::BiLink() : ArrayFunction("BiLink", 4) {}

	void BiLink::evaluate(double *value,
			   	      	std::vector<double const *> const &args,
            	        std::vector<std::vector<unsigned int> > const &dims ) const
	{
		auto nrv = JagsArray( value, dim(dims, args) );
		unsigned int pos1(*args[0]);
		unsigned int pos2(*args[1]);
		auto weight = JagsArray( args[2], dims[2] );
		auto net = JagsArray( args[3], dims[3] );
		nrv.copy( net );
		nrv.for_each(weight, [pos1,pos2](auto trg, auto w){ trg[pos2][pos1] = trg[pos1][pos2] = w; }, nrv.depth() - 2 - weight.depth() );
	}

	bool BiLink::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
		// if we have an array of values
		if(dims[2].size() != 1 || dims[2][0] != 1) {
			// sizes must match, or we can't create the matrix
			for(size_t i = 0; i < std::min(dims[2].size(), dims[3].size() - 2); ++i) {
				if(dims[2][i] != dims[3][i+2]) {
					return false;
				}
			}
		}

		return 
			(dims[0].size() == 1) && (dims[0][0] == 1) &&
			(dims[1].size() == 1) && (dims[1][0] == 1) &&
			(dims[3].size() >= 2) && (dims[3][0] + 1 == dims[3][1]);

	}

    bool BiLink::checkParameterValue(std::vector<double const *> const &args,
        	                              std::vector<std::vector<unsigned int> > const &dims) const
    {

    	return 
    		(*args[0] >= 1) && (*args[0] <= dims[3][0]) &&
    		(*args[1] >= 1) && (*args[1] <= dims[3][0]);

    }

    bool BiLink::checkParameterDiscrete(std::vector<bool> const &mask) const 
    {
    	return mask[0] && mask[1];
    }
    
    std::vector<unsigned int> 
    BiLink::dim(std::vector <std::vector<unsigned int> > const &dims,
            		 std::vector <double const *> const &values) const
    {
    	// If we have a single input, the dimensions are defined by the networks
    	if((dims[2].size() == 1) && (dims[2][0] == 1)) 
    		return dims[3];

    	// We need to identify which object has more dimensions
    	if(dims[2].size() + 2 <= dims[3].size())
    		return dims[3]; // Network is more complete

    	// We don't yet have multiple networks, so we create them
		std::vector<unsigned int> nrv{dims[3][0], dims[3][1]}; // First two dimensions are given by network structure
		nrv.insert(std::end(nrv),std::begin(dims[2]),std::end(dims[2])); // Take the rest from the parameter
		return jags::drop(nrv);    
	}

}
	