#include <util/dim.h>

#include "helpers/NetworkTemplate.hpp"

#include "Link.hpp"


namespace PDP {
	Link::Link(const char* name, bool bidir) : ArrayFunction(name, 4), m_bidir(bidir) {}

	void Link::evaluate(double *value,
			   	      	std::vector<double const *> const &args,
            	        std::vector<std::vector<unsigned int> > const &dims ) const
	{
        const auto innets = MakeNetworkTemplate( args[3], dims[3][0] );
        auto outnets = MakeNetworkTemplate( value, dim(dims, args)[0], innets );
        const auto pram = *args[0];
        const auto node1 = *args[1];
        const auto node2 = *args[2];
        outnets.entries().emplace_back( node1, node2, pram );
        if(m_bidir) {
            outnets.entries().emplace_back( node2, node1, pram );
        }
	}

	bool Link::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
        return 
            (dims[0].size() == 1) && (dims[0][0] == 1) &&
            (dims[1].size() == 1) && (dims[1][0] == 1) &&
            (dims[2].size() == 1) && (dims[1][0] == 1) &&
            (dims[3].size() == 1) &&
            (dims[3][0] >= NetworkTemplate<double>::s_header_length);       // Network must have at least a header
	}

    bool Link::checkParameterValue(std::vector<double const *> const &args,
        	                       std::vector<std::vector<unsigned int> > const &dims) const
    {

    	return (*args[0] >= 1) && (*args[1] >= 1) && (*args[2] >= 1);

    }

    bool Link::checkParameterDiscrete(std::vector<bool> const &mask) const 
    {
    	return mask[0] && mask[1] && mask[2];
    }
    
    bool Link::checkParameterFixed(std::vector<bool> const &mask) const {
        return mask[0] && mask[1] && mask[2] && mask[3];
    }


    std::vector<unsigned int> 
    Link::dim(std::vector <std::vector<unsigned int> > const &dims,
            		 std::vector <double const *> const &values) const
    {
        const auto innet = MakeNetworkTemplate( values[3], dims[3][0] );
        return { innet.extend( 1 + m_bidir) };
    }

}
	