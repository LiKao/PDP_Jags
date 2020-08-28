#include "config.h"

#include <cmath>
#include <algorithm>

#include <util/dim.h>

#include <boost/iterator/zip_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include <Eigen/Core>

#include <alloca.h>

#include "helpers/RingPointer.hpp"
#include "helpers/MemorySection.hpp"

#include "Tau.hpp"

namespace PDP {
	Tau::Tau() : jags::ArrayFunction( "tau", 2 ) {}

	void Tau::evaluate(double *value,
			   	       std::vector<double const *> const &args,
            	       std::vector<std::vector<unsigned int> > const &dims ) const
	{
        const auto dval = product(dims[0]);
        const auto dp   = product(dims[1]);
        const auto dout = dval*dp;

        if(dval == 1) {
            if(dp == 1) {
                *value = std::pow(*args[0] - 0.5, *args[1]);
                return;
            }

            Eigen::Map<const Eigen::ArrayXd> p(args[1], dp);
            Eigen::Map<Eigen::ArrayXd> eiout(value, dout);
            eiout = Eigen::ArrayXd::Constant(dout,*args[0] - 0.5).pow( p );
        }
        else {
            auto p = MakeRingPtr(args[1],dp);

            Eigen::Map<const Eigen::ArrayXd> eival(args[0], dval);
            Eigen::Map<Eigen::ArrayXd> m( reinterpret_cast<double*>( alloca( dval*sizeof(double) ) ), dval );
            m = eival - 0.5;

            Eigen::Map<Eigen::ArrayXd> eiout(value, dout);
            for(size_t i = 0; i < dp; ++i) {
                eiout.segment(i*dval,dval) = m.pow(*(p++));
            }
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