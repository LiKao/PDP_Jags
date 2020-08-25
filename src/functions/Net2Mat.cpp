#include <util/dim.h>

#include "helpers/NetworkTemplate.hpp"
#include "helpers/RingPointer.hpp"
#include "helpers/MemoryBlock.hpp"

#include "Net2Mat.hpp"

namespace PDP {
	Net2Mat::Net2Mat() : ArrayFunction("Net2Mat", 0) {}

	void Net2Mat::evaluate(double *value,
			   	      	std::vector<double const *> const &args,
            	        std::vector<std::vector<unsigned int> > const &dims ) const
	{
        const auto innet = MakeNetworkTemplate( args[0], dims[0][0] );
        const auto outdim = dim( dims, args );
        std::fill( value, value + product( outdim ), 0.0 );

        auto mat = MemoryBlock<2,double>( value, 
            static_cast<unsigned int>(innet.nnodes()) + 1, 
            static_cast<unsigned int>(innet.nnodes()) + 1 );

        std::vector<RingPointer<const double>> rargs;
        for(size_t i = 1; i < args.size(); ++i) {
            rargs.emplace_back(RingPointer( args[i], product( dims[i] ) ) );
        }

        const auto nnets = product(outdim.begin() + 2, outdim.end() );
        for(size_t i = 0; i < nnets; ++i ) {
            for(auto entry: innet.entries()) {
                mat[entry.row()][entry.column()] = *rargs[entry.pram()-1];
            }
            mat.next();
            std::for_each(rargs.begin(), rargs.end(), [](auto & rarg){ ++rarg; } );
        }
	}

	bool Net2Mat::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
        auto pdim = std::accumulate( 
            dims.begin() + 1, dims.end(), 
            std::vector<unsigned int>(), 
            [](auto lhs, auto rhs){ return (rhs.size() > lhs.size()) ? rhs : lhs; } );

        return 
            std::all_of( dims.begin() + 1, dims.end(), 
            [&pdim](auto dim){ 
                return ((dim.size() == 1) && (dim[0] == 1)) || 
                std::equal(dim.begin(), dim.end(), pdim.begin() ); } ) &&
            (dims[0].size() == 1) &&
            (dims[0][0] >= NetworkTemplate<double>::s_header_length);       // Network must have at least a header
	}

    bool Net2Mat::checkParameterValue(std::vector<double const *> const &args,
        	                       std::vector<std::vector<unsigned int> > const &dims) const
    {
        const auto innet = MakeNetworkTemplate( args[0], dims[0][0] );
        if(dims.size() != innet.nprams() + 1) {
            return false;
        }
    	return true;
    }

    bool Net2Mat::checkParameterDiscrete(std::vector<bool> const &mask) const 
    {
    	return true;
    }
    
    bool Net2Mat::checkParameterFixed(std::vector<bool> const &mask) const {
        return mask[0];
    }


    std::vector<unsigned int> 
    Net2Mat::dim( std::vector <std::vector<unsigned int> > const &dims,
            	  std::vector <double const *> const &values) const
    {
        const auto innet = MakeNetworkTemplate( values[0], dims[0][0] );
        std::vector<unsigned int> nrv = {
            static_cast<unsigned int>(innet.nnodes()) + 1,
            static_cast<unsigned int>(innet.nnodes()) + 1
        };

        // Get the dimension of the final object
        auto pdim = std::accumulate( 
            dims.begin() + 1, dims.end(), 
            std::vector<unsigned int>(), 
            [](auto lhs, auto rhs){ return (rhs.size() > lhs.size()) ? rhs : lhs; } );

        nrv.insert(nrv.end(), pdim.begin(), pdim.end() );
        return jags::drop( nrv );
    }

}
	