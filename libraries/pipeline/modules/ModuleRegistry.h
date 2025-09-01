#pragma once
#include "BaseModule.h"
#include <vector>
#include <functional>
#include <string>
#include <algorithm>

namespace Modules {

using ModuleFactory = std::function<BaseModule&()>;

class ModuleRegistry {
public:
    struct ModuleInfo {
        std::string name;
        ModuleFactory factory;
    };
    
    static ModuleRegistry& GetInstance() {
        static ModuleRegistry instance;
        return instance;
    }
    
    void RegisterModule(const std::string& name, ModuleFactory factory) {
        modules_.push_back({name, factory});
    }
    
    const std::vector<ModuleInfo>& GetModules() const {
        return modules_;
    }
    
private:
    std::vector<ModuleInfo> modules_;
};

} // namespace Modules

#define REGISTER_MODULE(ModuleClass) \
    namespace { \
        struct ModuleClass##Registrar { \
            ModuleClass##Registrar() { \
                Modules::ModuleRegistry::GetInstance().RegisterModule( \
                    #ModuleClass, \
                    []() -> BaseModule& { return ModuleClass::GetInstance(); } \
                ); \
            } \
        }; \
        static ModuleClass##Registrar g_##ModuleClass##Registrar; \
    }