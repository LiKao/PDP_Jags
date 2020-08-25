#include <cmath>
#include <algorithm>

#include <util/dim.h>

#include <boost/iterator/zip_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include "helpers/RingPointer.hpp"
#include "helpers/MemorySection.hpp"

#include "Tau.hpp"

namespace PDP {
	Tau::Tau() : jags::ArrayFunction( "tau", 2 ) {}

	void Tau::evaluate(double *value,
			   	       std::vector<double const *> const &args,
            	       std::vector<std::vector<unsigned int> > const &dims ) const
	{
		auto val = MakeRingPtr(args[0], product(dims[0]));
		auto p   = MakeRingPtr(args[1], product(dims[1]));
		auto out = MemorySection(value, product( dim( dims, args ) ) );

		for(auto & r: out) {
			r = std::pow( *(val++), *(p++) );
		}
	}

	bool Tau::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
		return true;
	}

    bool Tau::checkParameterValue( std::vector<double const *> const &args,
        	                       std::vector<std::vector<unsigned int> > const &dims) const
    {

    	return 
    		std::all_of(args[0], args[0] + product( dims[0] ), [](double d){return (d >= 0) && (d <= 1); } ) &&
    		std::all_of(args[1], args[1] + product( dims[1] ), [](double d){return d >= 0;});
    }

    
    std::vector<unsigned int> 
    Tau::dim(std::vector <std::vector<unsigned int> > const &dims,
            		 std::vector <double const *> const &values) const
    {
    	auto nrv = dims[0];
    	nrv.insert(nrv.end(), dims[1].begin(), dims[1].end() );
    	return jags::drop( nrv );
    }

}