#include <vector>

#include <function/ArrayFunction.h>

namespace PDP {
	class BiasInput : public jags::ArrayFunction 
	{
	public:
		BiasInput();

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

	};
}