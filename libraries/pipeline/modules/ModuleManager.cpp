#include "pch-il2cpp.h"
#include "ModuleManager.h"
#include "ModuleRegistry.h"
#include "../keybinds.h"
#include <iostream>
#include <algorithm>
#include <memory>

ModuleManager& ModuleManager::GetInstance() {
    static ModuleManager instance;
    return instance;
}

void ModuleManager::RegisterModule(std::unique_ptr<BaseModule> module) {
    std::cout << "[WARNING] Manual registration is deprecated; use automatic registry" << std::endl;
}

void ModuleManager::UnregisterModule(const std::string& name) {
    std::cout << "[WARNING] Manual unregistration is deprecated; use automatic registry" << std::endl;
}

BaseModule* ModuleManager::GetModule(const std::string& name) {
    for (auto* m : modules) {
        if (m && m->GetName() == name) return m;
    }
    return nullptr;
}

void ModuleManager::InitializeAll() {
    if (initialized) {
        std::cout << "[WARNING] ModuleManager already initialized" << std::endl;
        return;
    }

    std::cout << "[INFO] Initializing ModuleManager" << std::endl;

    modules.clear();
    const auto& regs = Modules::ModuleRegistry::GetInstance().GetModules();
    for (const auto& mi : regs) {
        try {
            BaseModule& mod = mi.factory();
            modules.push_back(&mod);
            mod.Initialize();
            std::cout << "[INFO] " << mod.GetName() << " initialized" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to initialize module '" << mi.name << "': " << e.what() << std::endl;
        }
    }

    initialized = true;
    std::cout << "[INFO] ModuleManager initialization complete" << std::endl;
}

void ModuleManager::ShutdownAll() {
    if (!initialized) {
        return;
    }

    std::cout << "[INFO] Shutting down ModuleManager" << std::endl;

    for (auto* m : modules) {
        if (!m) continue;
        try {
            m->Shutdown();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to shutdown module '" << m->GetName() << "': " << e.what() << std::endl;
        }
    }

    modules.clear();
    initialized = false;
    std::cout << "[INFO] ModuleManager shutdown complete" << std::endl;
}

void ModuleManager::UpdateAll() {
    if (!initialized) return;
    for (auto* m : modules) {
        if (!m || !m->IsEnabled()) continue;
        try {
            m->Update();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to update module '" << m->GetName() << "': " << e.what() << std::endl;
        }
    }
}

void ModuleManager::RenderAllGUI() {
    if (!initialized) return;
    for (auto* m : modules) {
        if (!m) continue;
        try {
            m->RenderGUI();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to render GUI for module '" << m->GetName() << "': " << e.what() << std::endl;
        }
    }
}

void ModuleManager::RenderAllOverlays() {
    if (!initialized) return;
    for (auto* m : modules) {
        if (!m || !m->IsEnabled()) continue;
        try {
            m->RenderOverlay();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to render overlay for module '" << m->GetName() << "': " << e.what() << std::endl;
        }
    }
}

void ModuleManager::ProcessAllHotkeys() {
    if (!initialized) return;
    for (auto* m : modules) {
        if (!m) continue;
        try {
            m->ProcessHotkeys();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to process hotkeys for module '" << m->GetName() << "': " << e.what() << std::endl;
        }
    }
    KeyBinds::UpdateKeyStates();
}

void ModuleManager::LoadAllConfigs() {
    if (!initialized) return;
    std::cout << "[INFO] Loading configurations for all modules" << std::endl;
    for (auto* m : modules) {
        if (!m) continue;
        try {
            m->LoadConfig();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to load config for module '" << m->GetName() << "': " << e.what() << std::endl;
        }
    }
}

void ModuleManager::SaveAllConfigs() {
    if (!initialized) return;
    std::cout << "[INFO] Saving configurations for all modules" << std::endl;
    for (auto* m : modules) {
        if (!m) continue;
        try {
            m->SaveConfig();
        } catch (const std::exception& e) {
            std::cout << "[ERROR] Failed to save config for module '" << m->GetName() << "': " << e.what() << std::endl;
        }
    }
}