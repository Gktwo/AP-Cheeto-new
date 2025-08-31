#pragma once
#include "BaseModule.h"
#include <vector>
#include <memory>
#include <string>

class ModuleManager {
public:
    static ModuleManager& GetInstance();
    
    // Module management
    void RegisterModule(std::unique_ptr<BaseModule> module);
    void UnregisterModule(const std::string& name);
    BaseModule* GetModule(const std::string& name);
    
    // Lifecycle management
    void InitializeAll();
    void ShutdownAll();
    void UpdateAll();
    
    // Rendering
    void RenderAllGUI();
    void RenderAllOverlays();
    
    // Input handling
    void ProcessAllHotkeys();
    
    // Configuration
    void LoadAllConfigs();
    void SaveAllConfigs();
    
    // Utility
    size_t GetModuleCount() const { return modules.size(); }
    const std::vector<std::unique_ptr<BaseModule>>& GetModules() const { return modules; }
    
private:
    ModuleManager() = default;
    ~ModuleManager() = default;
    ModuleManager(const ModuleManager&) = delete;
    ModuleManager& operator=(const ModuleManager&) = delete;
    
    std::vector<std::unique_ptr<BaseModule>> modules;
    bool initialized = false;
};

// Convenience macros
#define MODULE_MANAGER ModuleManager::GetInstance()