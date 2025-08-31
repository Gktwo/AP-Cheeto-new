#include "pch-il2cpp.h"
#include "ModuleManager.h"
#include "FPSModule.h"
#include "ESPModule.h"
#include "WorldSpeedModule.h"
#include <iostream>
#include <algorithm>

ModuleManager& ModuleManager::GetInstance() {
    static ModuleManager instance;
    return instance;
}

void ModuleManager::RegisterModule(std::unique_ptr<BaseModule> module) {
    if (module == nullptr) {
        std::cout << "[ERROR] Attempted to register null module" << std::endl;
        return;
    }
    
    // Check if module with same name already exists
    auto it = std::find_if(modules.begin(), modules.end(),
        [&module](const std::unique_ptr<BaseModule>& existing) {
            return existing->GetName() == module->GetName();
        });
    
    if (it != modules.end()) {
        std::cout << "[WARNING] Module '" << module->GetName() << "' already registered, replacing..." << std::endl;
        (*it)->Shutdown();
        *it = std::move(module);
    } else {
        std::cout << "[INFO] Registering module: " << module->GetName() << std::endl;
        modules.push_back(std::move(module));
    }
    
    // Initialize the module if manager is already initialized
    if (initialized && !modules.empty()) {
        modules.back()->Initialize();
    }
}

void ModuleManager::UnregisterModule(const std::string& name) {
    auto it = std::find_if(modules.begin(), modules.end(),
        [&name](const std::unique_ptr<BaseModule>& module) {
            return module->GetName() == name;
        });
    
    if (it != modules.end()) {
        std::cout << "[INFO] Unregistering module: " << name << std::endl;
        (*it)->Shutdown();
        modules.erase(it);
    } else {
        std::cout << "[WARNING] Module '" << name << "' not found for unregistration" << std::endl;
    }
}

BaseModule* ModuleManager::GetModule(const std::string& name) {
    auto it = std::find_if(modules.begin(), modules.end(),
        [&name](const std::unique_ptr<BaseModule>& module) {
            return module->GetName() == name;
        });
    
    return (it != modules.end()) ? it->get() : nullptr;
}

void ModuleManager::InitializeAll() {
    if (initialized) {
        std::cout << "[WARNING] ModuleManager already initialized" << std::endl;
        return;
    }
    
    std::cout << "[INFO] Initializing ModuleManager" << std::endl;
    
    // Initialize singleton modules directly
    try {
        FPSModule::GetInstance().Initialize();
        std::cout << "[INFO] FPSModule initialized" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to initialize FPSModule: " << e.what() << std::endl;
    }
    
    try {
        ESPModule::GetInstance().Initialize();
        std::cout << "[INFO] ESPModule initialized" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to initialize ESPModule: " << e.what() << std::endl;
    }
    
    try {
        WorldSpeedModule::GetInstance().Initialize();
        std::cout << "[INFO] WorldSpeedModule initialized" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to initialize WorldSpeedModule: " << e.what() << std::endl;
    }
    
    initialized = true;
    std::cout << "[INFO] ModuleManager initialization complete" << std::endl;
}

void ModuleManager::ShutdownAll() {
    if (!initialized) {
        return;
    }
    
    std::cout << "[INFO] Shutting down ModuleManager" << std::endl;
    
    try {
        FPSModule::GetInstance().Shutdown();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to shutdown FPSModule: " << e.what() << std::endl;
    }
    
    try {
        ESPModule::GetInstance().Shutdown();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to shutdown ESPModule: " << e.what() << std::endl;
    }
    
    try {
        WorldSpeedModule::GetInstance().Shutdown();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to shutdown WorldSpeedModule: " << e.what() << std::endl;
    }
    
    modules.clear();
    initialized = false;
    std::cout << "[INFO] ModuleManager shutdown complete" << std::endl;
}

void ModuleManager::UpdateAll() {
    if (!initialized) return;
    
    if (FPSModule::GetInstance().IsEnabled()) {
        try {
            FPSModule::GetInstance().Update();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to update FPSModule: " << e.what() << std::endl;
        }
    }
    
    if (ESPModule::GetInstance().IsEnabled()) {
        try {
            ESPModule::GetInstance().Update();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to update ESPModule: " << e.what() << std::endl;
        }
    }
    
    if (WorldSpeedModule::GetInstance().IsEnabled()) {
        try {
            WorldSpeedModule::GetInstance().Update();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to update WorldSpeedModule: " << e.what() << std::endl;
        }
    }
}

void ModuleManager::RenderAllGUI() {
    if (!initialized) return;
    
    try {
        FPSModule::GetInstance().RenderGUI();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to render GUI for FPSModule: " << e.what() << std::endl;
    }
    
    try {
        ESPModule::GetInstance().RenderGUI();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to render GUI for ESPModule: " << e.what() << std::endl;
    }
    
    try {
        WorldSpeedModule::GetInstance().RenderGUI();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to render GUI for WorldSpeedModule: " << e.what() << std::endl;
    }
}

void ModuleManager::RenderAllOverlays() {
    if (!initialized) return;
    
    if (FPSModule::GetInstance().IsEnabled()) {
        try {
            FPSModule::GetInstance().RenderOverlay();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to render overlay for FPSModule: " << e.what() << std::endl;
        }
    }
    
    if (ESPModule::GetInstance().IsEnabled()) {
        try {
            ESPModule::GetInstance().RenderOverlay();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to render overlay for ESPModule: " << e.what() << std::endl;
        }
    }
    
    if (WorldSpeedModule::GetInstance().IsEnabled()) {
        try {
            WorldSpeedModule::GetInstance().RenderOverlay();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to render overlay for WorldSpeedModule: " << e.what() << std::endl;
        }
    }
}

void ModuleManager::ProcessAllHotkeys() {
    if (!initialized) return;
    
    try {
        FPSModule::GetInstance().ProcessHotkeys();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to process hotkeys for FPSModule: " << e.what() << std::endl;
    }
    
    try {
        ESPModule::GetInstance().ProcessHotkeys();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to process hotkeys for ESPModule: " << e.what() << std::endl;
    }
    
    try {
        WorldSpeedModule::GetInstance().ProcessHotkeys();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to process hotkeys for WorldSpeedModule: " << e.what() << std::endl;
    }
}

void ModuleManager::LoadAllConfigs() {
    if (!initialized) return;
    
    std::cout << "[INFO] Loading configurations for all modules" << std::endl;
    
    try {
        FPSModule::GetInstance().LoadConfig();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to load config for FPSModule: " << e.what() << std::endl;
    }
    
    try {
        ESPModule::GetInstance().LoadConfig();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to load config for ESPModule: " << e.what() << std::endl;
    }
    
    try {
        WorldSpeedModule::GetInstance().LoadConfig();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to load config for WorldSpeedModule: " << e.what() << std::endl;
    }
}

void ModuleManager::SaveAllConfigs() {
    if (!initialized) return;
    
    std::cout << "[INFO] Saving configurations for all modules" << std::endl;
    
    try {
        FPSModule::GetInstance().SaveConfig();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to save config for FPSModule: " << e.what() << std::endl;
    }
    
    try {
        ESPModule::GetInstance().SaveConfig();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to save config for ESPModule: " << e.what() << std::endl;
    }
    
    try {
        WorldSpeedModule::GetInstance().SaveConfig();
    } catch (const std::exception& e) {
        std::cout << "[ERROR] Failed to save config for WorldSpeedModule: " << e.what() << std::endl;
    }
}