#include "BiLink.hpp"

#include <iostream>
#include <cstring>

namespace PDP {
	BiLink::BiLink() : ArrayFunction("BiLink", 4) {}

	void BiLink::evaluate(double *value,
			   	      	std::vector<double const *> const &args,
            	        std::vector<std::vector<unsigned int> > const &dims ) const
	{
		const auto dim = dims[3][0];
		std::memcpy(value, args[3], (dim+1)*dim*sizeof(double));
		value[(static_cast<size_t>(*args[0]) - 1)*dim + static_cast<size_t>(*args[1]) - 1] = *args[2];
		value[(static_cast<size_t>(*args[1]) - 1)*dim + static_cast<size_t>(*args[0]) - 1] = *args[2];
	}

	bool BiLink::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
		return 
			(dims[0].size() == 1) && (dims[0][0] == 1) &&
			(dims[1].size() == 1) && (dims[1][0] == 1) &&
			(dims[2].size() == 1) && (dims[1][0] == 1) &&
			(dims[3].size() == 2) && (dims[3][0] + 1 == dims[3][1]);

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
    	return dims[3];
    }

}
	