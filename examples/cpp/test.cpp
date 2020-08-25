#include <iostream>
#include <random>

#include "include/EigenAlgebra.hpp"
#include "include/PDP.hpp"

typedef Algebra::EigenAlgebra<double,6> DVecAlgebra;

constexpr DVecAlgebra::size_type nnodes = 6;
constexpr double p = 1;
constexpr size_t runs = 10000;
//constexpr size_t runs = 1;

int main(void) {
	double vals[4];
	double pattern[4];

	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<double> uniform_dist(0.51, 0.99);
	std::discrete_distribution<> discrete_dist({1, 1});
	for(size_t i = 0; i < runs; ++i) {
		for(int j = 0; j < 4; ++j) {
			vals[j] = uniform_dist(e1);
			pattern[j] = discrete_dist(e1)*2-1;
		}

		auto net = PDP::Network<nnodes>();
		net.biLink( 5, 1, pattern[0]*0.01);
		net.biLink( 5, 2, pattern[1]*0.01);
		net.biLink( 5, 3, pattern[2]*0.01);
		net.biLink( 5, 4, pattern[3]*0.01);

		net.biLink( 6, 1, -pattern[0]*0.01);
		net.biLink( 6, 2, -pattern[1]*0.01);
		net.biLink( 6, 3, -pattern[2]*0.01);
		net.biLink( 6, 4, -pattern[3]*0.01);

		net.biLink( 6, 5, -0.2 );

		net.input( 1, PDP::tau(vals[0], p) );
		net.input( 2, PDP::tau(vals[1], p) );
		net.input( 3, PDP::tau(vals[2], p) );
		net.input( 4, PDP::tau(vals[3], p) );

		std::cout << "W:\n" << net.w() << std::endl << std::endl;
		std::cout << "V:\n" << net.v() << std::endl << std::endl;
		
		auto init = DVecAlgebra::ZeroVector( nnodes );

		/*std::vector<std::pair<PDP::Network<DVecAlgebra>::scalar,DVecAlgebra::vector>> res;
		auto observer = [&res](const auto &act , auto t) { res.push_back(std::make_pair(t,act)); };*/

		net.simulate( init );
		std::cout << "Final state: " << init << std::endl;
		/*for(auto state: res) {
			std::cout << std::get<0>(state);
			for(int i = 0; i < std::get<1>(state).size(); ++i) {
				std::cout << ";" << std::get<1>(state)[i];
			}
			std::cout << "\n";
		}*/
	}
}