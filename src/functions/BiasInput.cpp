#include "BiasInput.hpp"

#include <iostream>
#include <cstring>

namespace PDP {
	BiasInput::BiasInput() : ArrayFunction("BiasInput", 3) {}

	void BiasInput::evaluate(double *value,
			   	      	std::vector<double const *> const &args,
            	        std::vector<std::vector<unsigned int> > const &dims ) const
	{
		const auto dim = dims[2][0];
		std::memcpy(value, args[2], (dim+1)*dim*sizeof(double));
		value[dim*dim + static_cast<size_t>(*args[0]) - 1] = *args[1];
	}

	bool BiasInput::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
		return 
			(dims[0].size() == 1) && (dims[0][0] == 1) &&
			(dims[1].size() == 1) && (dims[1][0] == 1) &&
			(dims[2].size() == 2) && (dims[2][0] + 1 == dims[2][1]);

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
    	return dims[2];
    }

}
	