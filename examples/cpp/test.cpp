#include <iostream>
#include <random>

#include "include/EigenAlgebra.hpp"
#include "include/PDP.hpp"

typedef Algebra::EigenAlgebra<double> DVecAlgebra;

constexpr DVecAlgebra::size_type nnodes = 6;
constexpr double p = 1;
constexpr size_t runs = 10000;

int main(void) {
	double vals[4];
	double pattern[4];

	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<double> uniform_dist(0.51, 0.99);
	std::discrete_distribution<> discrete_dist({1, 1});
	for(int i = 0; i < runs; ++i) {
		for(int j = 0; j < 4; ++j) {
			vals[j] = uniform_dist(e1);
			pattern[j] = discrete_dist(e1)*2-1;
		}

		auto w = DVecAlgebra::ZeroMatrix( nnodes, nnodes );
		w <<   0.0,   0.0,   0.0,   0.0,  pattern[0]*0.01, -pattern[0]*0.01,
		       0.0,   0.0,   0.0,   0.0,  pattern[1]*0.01, -pattern[1]*0.01,
		       0.0,   0.0,   0.0,   0.0,  pattern[2]*0.01, -pattern[2]*0.01,
	   	       0.0,   0.0,   0.0,   0.0,  pattern[3]*0.01, -pattern[3]*0.01,
		      pattern[0]*0.01, pattern[1]*0.01,  pattern[2]*0.01,  pattern[3]*0.01,   0.0, -0.2,
		      -pattern[0]*0.01,  -pattern[1]*0.01, -pattern[2]*0.01,  -pattern[3]*0.01,  -0.2,  0.0;

		auto v = DVecAlgebra::ZeroVector( nnodes );
		v << PDP::tau(vals[0], p), PDP::tau(vals[1], p), PDP::tau(vals[2], p), PDP::tau(vals[3], p), 0.0, 0.0;

		std::cout << "W:\n" << w << std::endl << std::endl;
		std::cout << "V:\n" << v << std::endl << std::endl;
		auto net = PDP::Network<DVecAlgebra>( w, v );
		auto init = DVecAlgebra::ZeroVector( nnodes );

		std::vector<std::pair<PDP::Network<DVecAlgebra>::scalar,DVecAlgebra::vector>> res;
		auto observer = [&res](const auto &act , auto t) { res.push_back(std::make_pair(t,act)); };

		net.simulate( init, observer );
		std::cout << "Final state: " << init << std::endl;
		for(auto state: res) {
			std::cout << std::get<0>(state);
			for(int i = 0; i < std::get<1>(state).size(); ++i) {
				std::cout << ";" << std::get<1>(state)[i];
			}
			std::cout << "\n";
		}
	}
}