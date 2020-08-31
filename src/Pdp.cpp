#include <module/Module.h>

#include "functions/Tau.hpp"
#include "functions/MakeNetwork.hpp"
#include "functions/Link.hpp"
#include "functions/BiasInput.hpp"
#include "functions/Simulate.hpp"
#include "functions/Net2Mat.hpp"
#include "functions/LuceChc.hpp"

namespace PDP {
	class PdpModule : public jags::Module {
	public:
		PdpModule() : jags::Module("Pdp") 
		{
			insert(new Tau);
			insert(new MakeNetwork);
			insert(new Link("Link",false));
			insert(new Link("BiLink",true));
			insert(new BiasInput);
			insert(new Simulate0);
			insert(new Net2Mat);
			insert(new LuceChc);
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