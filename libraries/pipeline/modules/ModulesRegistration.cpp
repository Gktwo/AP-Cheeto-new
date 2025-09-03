#include "pch-il2cpp.h"
#include "ModuleRegistry.h"
#include "FPSModule.h"
#include "ESPModule.h"
#include "WorldSpeedModule.h"
#include "FreeCam.h"
#include "NoFog.h"
#include "FpsUnlocker.h"
#include "UnityExplorerModule.h"

#define MODULES(X) \
    X(FPSModule) \
    X(ESPModule) \
    X(WorldSpeedModule)\
    X(FreeCam)\
    X(NoFog)\
    X(FpsUnlocker)\
    X(UnityExplorerModule)


#define REGISTER_ONE(Module) REGISTER_MODULE(Module)
#define REGISTER_ALL() MODULES(REGISTER_ONE)

REGISTER_ALL()