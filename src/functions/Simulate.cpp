#include "helpers/JagsArray.hpp"

#include "Simulate.hpp"

namespace PDP {
	Simulate0::Simulate0() : ArrayFunction("Simulate0", 2) {}

	void Simulate0::evaluate(double *value,
			   	      		 std::vector<double const *> const &args,
            	             std::vector<std::vector<unsigned int> > const &dims ) const
	{
		auto nrv = JagsArray(value, dim(dims,args));
        auto nets = JagsArray(args[0], dims[0]);
        auto decay = *args[1];
        nrv.for_each_block(nets, 2, [decay](auto trg, auto inp){
            const auto nnodes = inp.size() - 1;
            const auto W = Eigen::Map<const Algebra::matrix>(inp.get(), nnodes, nnodes);
            const auto V = Eigen::Map<const Algebra::vector>(inp[nnodes+1].get(), nnodes);
            auto state = Algebra::ZeroVector( nnodes );
            auto net = Network<Algebra>( W, V, decay );
            net.simulate( state );
            Eigen::Map<Algebra::vector>( trg.get(), nnodes ) = state;
        });
	}

	bool Simulate0::checkParameterDim(std::vector<std::vector<unsigned int> > const &dims) const
	{
		return (dims[0].size() >= 2) && (dims[0][0] + 1 == dims[0][1]) &&
               (dims[1].size() == 1) && (dims[1][0] == 1);
	}

    bool Simulate0::checkParameterValue(std::vector<double const *> const &args,
        	                              std::vector<std::vector<unsigned int> > const &dims) const
    {
    	return *args[1] > 0;
    }
  
    std::vector<unsigned int> 
    Simulate0::dim(std::vector <std::vector<unsigned int> > const &dims,
            		 std::vector <double const *> const &values) const
    {
        // We drop the second part of the network matrix, 
        // but retain the structure representing different networks
        std::vector<unsigned int> nrv{ dims[0][0] };
        nrv.insert(std::end(nrv), dims[0].cbegin() + 2, dims[0].end());
    	return nrv;
    }

}
	