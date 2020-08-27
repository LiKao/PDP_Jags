#include <iostream>
#include <random>

#include "include/PDP.hpp"

constexpr size_t nnodes = 8;
constexpr double p = 1.5;
constexpr size_t runs = 20000;
//constexpr size_t runs = 1;

int main(void) {

	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_real_distribution<double> uniform_dist(0.51, 0.99);
	std::discrete_distribution<> discrete_dist({1, 1});
	for(size_t i = 0; i < runs; ++i) {
		auto net = PDP::Network( nnodes );

		for(size_t j = 1; j <= nnodes - 2; ++j) {
			const auto p1 = discrete_dist(e1)*2-1;
			const auto p2 = discrete_dist(e1)*2-1;
			net.biLink( nnodes-1, j, p1*0.01);
			net.biLink( nnodes,   j, p2*0.01);

			const auto v = uniform_dist(e1);
			net.input( j, PDP::tau(v, p) );	
		}		
	
		net.biLink( nnodes, nnodes-1, -0.2 );

		std::cout << "W:\n" << net.w() << std::endl << std::endl;
		std::cout << "V:\n" << net.v() << std::endl << std::endl;
		
		Eigen::VectorXd init = Eigen::VectorXd::Zero( nnodes );

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