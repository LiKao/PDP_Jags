#ifndef NET2MAT_HPP
#define NET2MAT_HPP

#include <vector>

#include <function/ArrayFunction.h>

namespace PDP {
	class Net2Mat : public jags::ArrayFunction 
	{
	public:
		Net2Mat();

		void evaluate(double *value,
			   	      std::vector<double const *> const &args,
            	      std::vector<std::vector<unsigned int> > const &dims ) const override;

	    bool checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const override;

    	bool checkParameterValue(std::vector<double const *> const &args,
        	                     std::vector<std::vector<unsigned int> > const &dims) const override;

    	bool checkParameterDiscrete(std::vector<bool> const &mask) const override;
    
    	std::vector<unsigned int> 
    	dim(std::vector <std::vector<unsigned int> > const &dims,
           	std::vector <double const *> const &values) const override;

        virtual bool checkParameterFixed(std::vector<bool> const &mask) const override;
	};
}

#endif // NET2MAT_HPP