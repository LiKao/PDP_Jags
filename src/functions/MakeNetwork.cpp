#include "MakeNetwork.hpp"

namespace PDP {
	MakeNetwork::MakeNetwork() : ArrayFunction("MakeNetwork", 1) {}

	void MakeNetwork::evaluate(double *value,
			   	      		   std::vector<double const *> const &args,
            	               std::vector<std::vector<unsigned int> > const &dims ) const
	{

	}

	bool MakeNetwork::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
		return dims[0].size() == 1;
	}

    bool MakeNetwork::checkParameterValue(std::vector<double const *> const &args,
        	                              std::vector<std::vector<unsigned int> > const &dims) const
    {
    	return *args[0] > 0;
    }

    bool MakeNetwork::checkParameterDiscrete(std::vector<bool> const &mask) const 
    {
    	return mask[0];
    }
    
    std::vector<unsigned int> 
    MakeNetwork::dim(std::vector <std::vector<unsigned int> > const &dims,
            		 std::vector <double const *> const &values) const
    {
    	return {
    		static_cast<unsigned int>(*values[0]),
    		static_cast<unsigned int>(*values[0]) + 1
    	};
    }

}
	