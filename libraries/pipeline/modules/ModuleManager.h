#pragma once
#include "BaseModule.h"
#include "ModuleRegistry.h"
#include <vector>
#include <string>
#include <memory>

class ModuleManager {
public:
    static ModuleManager& GetInstance();
    
    void InitializeAll();
    void ShutdownAll();
    void UpdateAll();
    
    void RenderAllGUI();
    void RenderAllOverlays();
    
    void ProcessAllHotkeys();
    
    void LoadAllConfigs();
    void SaveAllConfigs();
    
    size_t GetModuleCount() const { return modules.size(); }
    const std::vector<BaseModule*>& GetModules() const { return modules; }

    void RegisterModule(std::unique_ptr<BaseModule> module);
    void UnregisterModule(const std::string& name);
    BaseModule* GetModule(const std::string& name);
    
private:
    ModuleManager() = default;
    ~ModuleManager() = default;
    ModuleManager(const ModuleManager&) = delete;
    ModuleManager& operator=(const ModuleManager&) = delete;
    
    std::vector<BaseModule*> modules;
    bool initialized = false;
};

#define MODULE_MANAGER ModuleManager::GetInstance()