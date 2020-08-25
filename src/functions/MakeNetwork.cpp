#include <algorithm>
#include <numeric>


#include "MakeNetwork.hpp"
#include "helpers/NetworkTemplate.hpp"

#include <iostream>

namespace PDP {

	MakeNetwork::MakeNetwork() : ArrayFunction("MakeNetwork", 1) {}

	void MakeNetwork::evaluate(double *value,
			   	      		   std::vector<double const *> const &args,
            	               std::vector<std::vector<unsigned int> > const &dims ) const
	{
        NetworkTemplate<double>::init(value, *args[0]);
	}

	bool MakeNetwork::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
		return dims.size() >= 1 && dims[0][0] == 1;
	}

    bool MakeNetwork::checkParameterValue(std::vector<double const *> const &args,
        	                              std::vector<std::vector<unsigned int> > const &dims) const
    {
    	return std::all_of(args.begin(), args.end(), [](auto d){ return *d > 1;} );
    }

    bool MakeNetwork::checkParameterDiscrete(std::vector<bool> const &mask) const 
    {
    	return mask[0];
    }
    
    std::vector<unsigned int> 
    MakeNetwork::dim(std::vector <std::vector<unsigned int> > const &dims,
            		 std::vector <double const *> const &values) const
    {
    	return { NetworkTemplate<double>::s_header_length };
    }

    bool MakeNetwork::checkParameterFixed(std::vector<bool> const &mask) const {
        return mask[0];

    }

}
	