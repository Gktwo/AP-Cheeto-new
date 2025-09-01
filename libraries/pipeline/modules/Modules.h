#pragma once

#include "BaseModule.h"
#include "ModuleManager.h"

namespace Modules {
    inline void InitializeSystem() {
        MODULE_MANAGER.InitializeAll();
    }
    
    inline void ShutdownSystem() {
        MODULE_MANAGER.ShutdownAll();
    }
}