#include <iostream>
#include <random>

#include "include/EigenAlgebra.hpp"
#include "include/PDP.hpp"

typedef Algebra::EigenAlgebra<double> DVecAlgebra;

constexpr DVecAlgebra::size_type nnodes = 6;
constexpr double p = 4;

int main(void) {
	/*double vals[4] = {0.6818182, 0.6363636, 0.6363636, 0.5909091};

	auto w = DVecAlgebra::ZeroMatrix( nnodes, nnodes );
	w <<   0.0,   0.0,   0.0,   0.0,   0.01, -0.01,
	       0.0,   0.0,   0.0,   0.0,  -0.01,  0.01,
	       0.0,   0.0,   0.0,   0.0,  -0.01, -0.01,
   	       0.0,   0.0,   0.0,   0.0,  -0.01,  0.01,
	      0.01, -0.01, -0.01, -0.01,    0.0,  -0.2,
	     -0.01,  0.01, -0.01,  0.01,   -0.2,   0.0;

	

	auto v = DVecAlgebra::ZeroVector( nnodes );
	v << PDP::tau(vals[0], p), PDP::tau(vals[1], p), PDP::tau(vals[2], p), PDP::tau(vals[3], p), 0.0, 0.0;

	std::cout << "W:\n" << w << std::endl << std::endl;
	std::cout << "V:\n" << v << std::endl << std::endl;
	auto net = PDP::Network<DVecAlgebra>( w, v );
	auto init = DVecAlgebra::ZeroVector( nnodes );

	std::vector<std::pair<PDP::Network<DVecAlgebra>::scalar,DVecAlgebra::vector>> res;
	auto observer = [&res](const auto &act , auto t) { res.push_back(std::make_pair(t,act)); };

	net.simulate( init );
	std::cout << "Final state: " << init << std::endl;*/
	/*for(auto state: res) {
		std::cout << std::get<0>(state);
		for(int i = 0; i < std::get<1>(state).size(); ++i) {
			std::cout << ";" << std::get<1>(state)[i];
		}
		std::cout << "\n";
	}*/
}