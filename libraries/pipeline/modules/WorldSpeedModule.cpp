#include "pch-il2cpp.h"
#include "WorldSpeedModule.h"
#include "../keybinds.h"
#include "pipeline/HookManager.h"
#include "imgui/imgui.h"
#include <iostream>

// Static instance pointer for hook access
static WorldSpeedModule* g_worldSpeedModule = nullptr;

WorldSpeedModule::WorldSpeedModule() 
    : BaseModule("World Speed"), 
      world_speed_enabled(false), 
      world_speed_value(1.0f), 
      toggle_key(VK_F7) {
    g_worldSpeedModule = this;
}

void WorldSpeedModule::Initialize() {
    std::cout << "[INFO] World Speed Module initialized" << std::endl;
    LoadConfig();
}

void WorldSpeedModule::Shutdown() {
    if (world_speed_enabled) {
        DisableWorldSpeed();
    }
    SaveConfig();
    std::cout << "[INFO] World Speed Module shutdown" << std::endl;
    g_worldSpeedModule = nullptr;
}

void WorldSpeedModule::Update() {
    // Update logic if needed
}

void WorldSpeedModule::RenderGUI() {
    if (ImGui::CollapsingHeader("World Speed")) {
        ImGui::Indent();
        
        // World speed toggle
        if (ImGui::Checkbox("Enable World Speed", &world_speed_enabled)) {
            if (world_speed_enabled) {
                EnableWorldSpeed();
                std::cout << "[INFO] World Speed enabled with value: " << world_speed_value << std::endl;
            } else {
                DisableWorldSpeed();
                std::cout << "[INFO] World Speed disabled" << std::endl;
            }
            SetEnabled(world_speed_enabled);
        }
        
        // Reset button
        ImGui::SameLine();
        if (ImGui::Button("Reset")) {
            ResetSpeed();
        }
        
        // Speed slider (only show when enabled)
        if (world_speed_enabled) {
            ImGui::Indent();
            ImGui::SliderFloat("Speed Value", &world_speed_value, 0.1f, 20.0f, "%.1f");
            ImGui::Unindent();
        }
        
        // Hotkey configuration
        ImGui::Text("Toggle Key: %s", KeyBinds::ToString(toggle_key));
        ImGui::SameLine();
        if (ImGui::Button("Change##world_speed_key")) {
            // Key binding logic can be implemented here
        }
        
        // Current status display
        // ImGui::Text("Status: ");
        // ImGui::SameLine();
        // if (world_speed_enabled) {
        //     ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Active (%.1fx)", world_speed_value);
        // } else {
        //     ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "Disabled");
        // }
        
        ImGui::Unindent();
    }
}

void WorldSpeedModule::RenderOverlay() {
    //if (!enabled || !world_speed_enabled) return;
    //
    //// Display world speed overlay in top-right corner
    //ImVec2 window_size = ImGui::GetIO().DisplaySize;
    //ImVec2 pos(window_size.x - 150.0f, 10.0f);
    //
    //char speed_text[64];
    //sprintf_s(speed_text, "World Speed: %.1fx", world_speed_value);
    //
    //ImVec4 color = (world_speed_value == 1.0f) ? 
    //    ImVec4(1.0f, 1.0f, 1.0f, 1.0f) :  // White for normal speed
    //    ImVec4(1.0f, 1.0f, 0.0f, 1.0f);   // Yellow for modified speed
    //
    //ImGui::GetForegroundDrawList()->AddText(
    //    pos, 
    //    ImGui::ColorConvertFloat4ToU32(color), 
    //    speed_text
    //);
}

void WorldSpeedModule::ProcessHotkeys() {
    if (KeyBinds::IsKeyPressed(toggle_key)) {
        world_speed_enabled = !world_speed_enabled;
        if (world_speed_enabled) {
            EnableWorldSpeed();
        } else {
            DisableWorldSpeed();
        }
        SetEnabled(world_speed_enabled);
    }
}

void WorldSpeedModule::LoadConfig() {
    // Load configuration from file or registry
    // For now, use default values
}

void WorldSpeedModule::SaveConfig() {
    // Save configuration to file or registry
}

void WorldSpeedModule::EnableWorldSpeed() {
    HookManager::install(app::AzurWorld_OnUpdate, AzurWorld_OnUpdate_world_speed_Hook);
    
}

void WorldSpeedModule::DisableWorldSpeed() {
    app::Time_1_set_timeScale(1.0f, nullptr);
    HookManager::detach(AzurWorld_OnUpdate_world_speed_Hook);
    
}

void WorldSpeedModule::ResetSpeed() {
    world_speed_value = 1.0f;
    std::cout << "[INFO] World Speed reset to 1.0x" << std::endl;
}

void WorldSpeedModule::AzurWorld_OnUpdate_world_speed_Hook(app::AzurWorld* __this, MethodInfo* method) {
    if (g_worldSpeedModule && g_worldSpeedModule->world_speed_enabled) {
        app::Time_1_set_timeScale(g_worldSpeedModule->world_speed_value, nullptr);
    }
    CALL_ORIGIN(AzurWorld_OnUpdate_world_speed_Hook, __this, method);
}