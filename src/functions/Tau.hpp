#include <vector>

#include <function/ScalarFunction.h>

namespace PDP {
	class Tau : public jags::ScalarFunction 
	{
	public:
		Tau();
		double evaluate(std::vector<double const *> const &args) const override;
		bool checkParameterValue(std::vector<double const *> const &args) const override;
		bool isPower(std::vector<bool> const &mask, std::vector<bool> const &isfixed) const override;
	};
}