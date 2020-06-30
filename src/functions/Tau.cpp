#include <cmath>
#include "Tau.hpp"

namespace PDP {
		Tau::Tau() : jags::ScalarFunction( "tau", 2 ) {}

		double Tau::evaluate(std::vector<double const *> const &args) const
		{
			return std::pow(*args[0] - 0.5, *args[1]);
		}

		bool Tau::checkParameterValue(std::vector<double const *> const &args) const 
		{
			return 
				(*args[0] >= 0) &&
				(*args[0] <= 1) &&
				(*args[1] >= 0);

		}

		bool Tau::isPower(std::vector<bool> const &mask, std::vector<bool> const &isfixed) const
		{
			return false;
		}

}