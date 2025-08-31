#pragma once
#include "BaseModule.h"
#include <vector>
#include <functional>
#include <string>
#include <algorithm>

namespace Modules {

// Module factory function type
using ModuleFactory = std::function<BaseModule&()>;

// Module registry for automatic registration
class ModuleRegistry {
public:
    struct ModuleInfo {
        std::string name;
        ModuleFactory factory;
        int priority; // Lower number = higher priority
    };
    
    static ModuleRegistry& GetInstance() {
        static ModuleRegistry instance;
        return instance;
    }
    
    // Register a module with automatic registration
    void RegisterModule(const std::string& name, ModuleFactory factory, int priority = 100) {
        modules_.push_back({name, factory, priority});
        // Sort by priority after each registration
        std::sort(modules_.begin(), modules_.end(), 
                 [](const ModuleInfo& a, const ModuleInfo& b) {
                     return a.priority < b.priority;
                 });
    }
    
    // Get all registered modules
    const std::vector<ModuleInfo>& GetModules() const {
        return modules_;
    }
    
private:
    std::vector<ModuleInfo> modules_;
};

} // namespace Modules

// Macro for automatic module registration
#define REGISTER_MODULE(ModuleClass, Priority) \
    namespace { \
        struct ModuleClass##Registrar { \
            ModuleClass##Registrar() { \
                Modules::ModuleRegistry::GetInstance().RegisterModule( \
                    #ModuleClass, \
                    []() -> Modules::BaseModule& { return ModuleClass::GetInstance(); }, \
                    Priority \
                ); \
            } \
        }; \
        static ModuleClass##Registrar g_##ModuleClass##Registrar; \
    }