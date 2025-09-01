#include "pch-il2cpp.h"
#include "ModuleRegistry.h"
#include "FPSModule.h"
#include "ESPModule.h"
#include "WorldSpeedModule.h"

#define MODULES(X) \
    X(FPSModule) \
    X(ESPModule) \
    X(WorldSpeedModule)

#define REGISTER_ONE(Module) REGISTER_MODULE(Module)
#define REGISTER_ALL() MODULES(REGISTER_ONE)

REGISTER_ALL()