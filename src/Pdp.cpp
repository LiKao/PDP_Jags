#include <module/Module.h>

#include "functions/Tau.hpp"
#include "functions/MakeNetwork.hpp"

namespace PDP {
	class PdpModule : public jags::Module {
	public:
		PdpModule() : jags::Module("Pdp") 
		{
			insert(new Tau);
			insert(new MakeNetwork);
		}
		~PdpModule() 
		{
			for(auto f : functions()) 
				delete f;
		}
	};
}

// Explicit instantiation of the module
PDP::PdpModule _PdpModule;