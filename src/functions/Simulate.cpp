#include "helpers/JagsArray.hpp"

#include "include/EigenAlgebra.hpp"
#include "include/PDP.hpp"

#include "Simulate.hpp"

namespace PDP {
	Simulate0::Simulate0() : ArrayFunction("Simulate0", 2) {}

    namespace {
        template<Eigen::Index _size>
        struct simulator {
            typedef Algebra::EigenAlgebra<double, _size>   Algebra;

            template<typename T1, typename T2>
            static void run(const T1 & inp, typename Algebra::scalar decay, T2 & trg ) {
                const auto nnodes = inp.size() - 1;
                const auto W = Eigen::Map<const typename Algebra::matrix>(inp.get(), nnodes, nnodes);
                const auto V = Eigen::Map<const typename Algebra::vector>(inp[nnodes+1].get(), nnodes);

                auto net = Network<Algebra>( W, V, decay );
                auto state = Algebra::ZeroVector( net.nnodes() );
                net.simulate( state );
                Eigen::Map<typename Algebra::vector>( trg.get(), nnodes ) = state;
            }
        };
    }

	void Simulate0::evaluate(double *value,
			   	      		 std::vector<double const *> const &args,
            	             std::vector<std::vector<unsigned int> > const &dims ) const
	{
		auto nrv = JagsArray(value, dim(dims,args));
        auto nets = JagsArray(args[0], dims[0]);
        auto decay = *args[1];
        nrv.for_each_block(nets, 2, [decay](auto trg, auto inp){ 
            const auto nnodes = inp.size() - 1;
            switch(nnodes) {
                case 1:
                    simulator<1>::run( inp, decay, trg );
                    break;
                case 2:
                    simulator<2>::run( inp, decay, trg );
                    break;
                case 3:
                    simulator<3>::run( inp, decay, trg );
                    break;
                case 4:
                    simulator<4>::run( inp, decay, trg );
                    break;
                case 5:
                    simulator<5>::run( inp, decay, trg );
                    break;
                case 6:
                    simulator<6>::run( inp, decay, trg );
                    break;
                case 7:
                    simulator<7>::run( inp, decay, trg );
                    break;
                case 8:
                    simulator<8>::run( inp, decay, trg );
                    break;
                case 9:
                    simulator<9>::run( inp, decay, trg );
                    break;
                case 10:
                    simulator<10>::run( inp, decay, trg );
                    break;
                case 11:
                    simulator<11>::run( inp, decay, trg );
                    break;
                case 12:
                    simulator<12>::run( inp, decay, trg );
                    break;
                case 13:
                    simulator<13>::run( inp, decay, trg );
                    break;
                case 14:
                    simulator<14>::run( inp, decay, trg );
                    break;
                case 15:
                    simulator<15>::run( inp, decay, trg );
                    break;
                case 16:
                    simulator<16>::run( inp, decay, trg );
                    break;
                case 17:
                    simulator<17>::run( inp, decay, trg );
                    break;
                case 18:
                    simulator<18>::run( inp, decay, trg );
                    break;
                case 19:
                    simulator<19>::run( inp, decay, trg );
                    break;
                case 20:
                    simulator<20>::run( inp, decay, trg );
                    break;
                default:
                    simulator<Eigen::Dynamic>::run( inp, decay, trg );
                    break;
            }
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
	