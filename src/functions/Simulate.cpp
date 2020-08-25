#include <util/dim.h>

#include "helpers/NetworkTemplate.hpp"
#include "helpers/MemoryBlock.hpp"
#include "helpers/RingPointer.hpp"

#include "include/EigenAlgebra.hpp"
#include "include/PDP.hpp"

#include "Simulate.hpp"

namespace PDP {
	Simulate0::Simulate0() : ArrayFunction("Simulate0", 0) {}

	void Simulate0::evaluate(double *value,
			   	      		 std::vector<double const *> const &args,
            	             std::vector<std::vector<unsigned int> > const &dims ) const
	{
        const auto innet = MakeNetworkTemplate( args[0], dims[0][0] );
        const auto decay = *args[1];
        const auto outdim = dim( dims, args );
        std::fill( value, value + product( outdim ), 0.0 );

        auto mat = MemoryBlock<1,double>( value, static_cast<unsigned int>(innet.nnodes()) );

        std::vector<RingPointer<const double>> rargs;
        for(size_t i = 2; i < args.size(); ++i) {
            rargs.emplace_back(RingPointer( args[i], product( dims[i] ) ) );
        }

        const auto nnets = product(outdim.begin() + 1, outdim.end() );
        for(size_t i = 0; i < nnets; ++i ) {
            auto net = PDP::Network( innet.nnodes(), decay );
            for(auto entry: innet.entries()) {
                if(entry.column() == 0) {
                    net.input(entry.row(), *rargs[entry.pram()-1]);
                } 
                else {
                    net.link(entry.row(), entry.column(), *rargs[entry.pram()-1]);
                }
            }
            Eigen::VectorXd state = Eigen::VectorXd::Zero( net.nnodes() );
            net.simulate( state );
            mat = state.data();
            mat.next();
            std::for_each(rargs.begin(), rargs.end(), [](auto & rarg){ ++rarg; } );
        }
	}

	bool Simulate0::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
    {
        auto pdim = std::accumulate( 
            dims.begin() + 2, dims.end(), 
            std::vector<unsigned int>(), 
            [](auto lhs, auto rhs){ return (rhs.size() > lhs.size()) ? rhs : lhs; } );

        return 
            std::all_of( dims.begin() + 2, dims.end(), 
                [&pdim](auto dim){ 
                    return ((dim.size() == 1) && (dim[0] == 1)) || 
                    std::equal(dim.begin(), dim.end(), pdim.begin() ); } ) &&
            (dims[0].size() == 1) &&
            (dims[0][0] >= NetworkTemplate<double>::s_header_length) &&      // Network must have at least a header
            (dims[1].size() == 1) && (dims[1][0] == 1);                      // decay must be single value
	}

    bool Simulate0::checkParameterValue(std::vector<double const *> const &args,
        	                              std::vector<std::vector<unsigned int> > const &dims) const
    {
    	const auto innet = MakeNetworkTemplate( args[0], dims[0][0] );
        if(dims.size() != innet.nprams() + 2) {
            return false;
        }
        return true;
    }

    bool Simulate0::checkParameterFixed(std::vector<bool> const &mask) const {
        return mask[0] && mask[1];
    }
  
    std::vector<unsigned int> 
    Simulate0::dim(std::vector <std::vector<unsigned int> > const &dims,
            		 std::vector <double const *> const &values) const
    {
        const auto innet = MakeNetworkTemplate( values[0], dims[0][0] );
        std::vector<unsigned int> nrv = { static_cast<unsigned int>(innet.nnodes()) };

        // Get the dimension of the final object
        auto pdim = std::accumulate( 
            dims.begin() + 2, dims.end(), 
            std::vector<unsigned int>(), 
            [](auto lhs, auto rhs){ return (rhs.size() > lhs.size()) ? rhs : lhs; } );

        nrv.insert(nrv.end(), pdim.begin(), pdim.end() );
        return jags::drop( nrv );
    }
}