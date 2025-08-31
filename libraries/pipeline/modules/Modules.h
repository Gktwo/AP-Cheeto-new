#pragma once

// Module System Headers
#include "BaseModule.h"
#include "ModuleManager.h"

// Individual Module Headers
#include "FPSModule.h"
#include "ESPModule.h"
#include "WorldSpeedModule.h"

// Convenience macros for module system
#define REGISTER_MODULE(ModuleClass) MODULE_MANAGER.RegisterModule(std::make_unique<ModuleClass>())
#define GET_MODULE(ModuleName) MODULE_MANAGER.GetModule(ModuleName)
#define UNREGISTER_MODULE(ModuleName) MODULE_MANAGER.UnregisterModule(ModuleName)

// Module system initialization helper
namespace Modules {
    inline void InitializeSystem() {
        MODULE_MANAGER.InitializeAll();
    }
    
    inline void ShutdownSystem() {
        MODULE_MANAGER.ShutdownAll();
    }
    
    inline void RegisterDefaultModules() {
        REGISTER_MODULE(FPSModule);
        REGISTER_MODULE(ESPModule);
        REGISTER_MODULE(WorldSpeedModule);
    }
}