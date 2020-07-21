#include <module/Module.h>

#include "functions/Tau.hpp"
#include "functions/MakeNetwork.hpp"
#include "functions/Link.hpp"
#include "functions/BiLink.hpp"
#include "functions/BiasInput.hpp"
#include "functions/Simulate.hpp"

namespace PDP {
	class PdpModule : public jags::Module {
	public:
		PdpModule() : jags::Module("Pdp") 
		{
			insert(new Tau);
			insert(new MakeNetwork);
			insert(new Link);
			insert(new BiLink);
			insert(new BiasInput);
			insert(new Simulate0);
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