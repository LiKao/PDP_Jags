#ifndef LINK_HPP
#define LINK_HPP

#include <vector>

#include <function/ArrayFunction.h>

namespace PDP {
	class Link : public jags::ArrayFunction 
	{
	public:
		Link(const char* name, bool bidir);

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
    private:
    	bool m_bidir;

	};
}

#endif // LINK_HPP