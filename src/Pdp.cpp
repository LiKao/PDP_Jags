#include <module/Module.h>

namespace PDP {
	class PDPModule : public jags::Module {
	public:
		PDPModule() : jags::Module("PDP") {}
		~PDPModule() {}
	};
}

// Explicit instantiation of the module
PDP::PDPModule _PDPModule;