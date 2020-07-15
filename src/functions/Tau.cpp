#include <cmath>
#include <algorithm>

#include <util/dim.h>

#include "helpers/JagsArray.hpp"
#include "Tau.hpp"

namespace PDP {
	Tau::Tau() : jags::ArrayFunction( "tau", 2 ) {}

	void Tau::evaluate(double *value,
			   	       std::vector<double const *> const &args,
            	       std::vector<std::vector<unsigned int> > const &dims ) const
	{
		auto val = JagsArray(args[0], {dims[0][0]});
		auto p = JagsArray(args[1], {dims[1][0]});
		for(auto arr1: JagsArray(value, {dims[0][0],dims[1][0]})) {
			for(auto arr2: arr1) {
				arr2 = std::pow(val[arr2.index()]-0.5, p[arr1.index()]);
			}
		}
	}

	bool Tau::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
		return (dims[0].size() == 1) && (dims[1].size() == 1);
	}

    bool Tau::checkParameterValue(std::vector<double const *> const &args,
        	                              std::vector<std::vector<unsigned int> > const &dims) const
    {

    	return 
    		std::all_of(args[0], args[0] + dims[0][0], [](double d){return (d >= 0) && (d <= 1); } ) &&
    		std::all_of(args[1], args[1] + dims[1][0], [](double d){return d >= 0;});
    }

    
    std::vector<unsigned int> 
    Tau::dim(std::vector <std::vector<unsigned int> > const &dims,
            		 std::vector <double const *> const &values) const
    {
    	return jags::drop({dims[0][0], dims[1][0]});
    }

}