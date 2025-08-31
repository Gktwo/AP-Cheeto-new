#include "pch-il2cpp.h"
#include "FPSModule.h"
#include "../keybinds.h"
#include "imgui/imgui.h"
#include <iostream>

FPSModule::FPSModule() : BaseModule("FPS Monitor"), show_fps(true), toggle_key(VK_F5) {
}

void FPSModule::Initialize() {
    std::cout << "[INFO] FPS Module initialized" << std::endl;
    LoadConfig();
}

void FPSModule::Shutdown() {
    SaveConfig();
    std::cout << "[INFO] FPS Module shutdown" << std::endl;
}

void FPSModule::Update() {
    // Update logic if needed
}

void FPSModule::RenderGUI() {
    if (ImGui::CollapsingHeader("FPS Monitor")) {
        ImGui::Indent();
        
        // FPS display toggle
        if (ImGui::Checkbox("Show FPS Overlay", &show_fps)) {
            SetEnabled(show_fps);
        }
        
        // Hotkey configuration
        ImGui::Text("Toggle Key: %s", KeyBinds::ToString(toggle_key));
        ImGui::SameLine();
        if (ImGui::Button("Change##fps_key")) {
            // Key binding logic can be implemented here
        }
        
        // Display current FPS info
        float fps = ImGui::GetIO().Framerate;
        float frame_time = 1000.0f / fps;
        
        ImGui::Text("Current FPS: ");
        ImGui::SameLine();
        ImGui::TextColored(GetFPSColor(fps), "%.1f", fps);
        
        ImGui::Text("Frame Time: ");
        ImGui::SameLine();
        ImGui::TextColored(GetFrameTimeColor(frame_time), "%.2f ms", frame_time);
        
        ImGui::Unindent();
    }
}

void FPSModule::RenderOverlay() {
    if (!enabled || !show_fps) return;
    
    float fps = ImGui::GetIO().Framerate;
    float frame_time = 1000.0f / fps;
    
    // Position at top-left corner
    ImVec2 pos(10.0f, 10.0f);
    
    // Draw FPS
    ImGui::GetForegroundDrawList()->AddText(
        pos, 
        ImGui::ColorConvertFloat4ToU32(GetFPSColor(fps)), 
        ("FPS: " + std::to_string((int)fps)).c_str()
    );
    
    // Draw frame time below FPS
    pos.y += 25.0f;
    char frame_time_str[32];
    sprintf_s(frame_time_str, "Frame Time: %.2f ms", frame_time);
    ImGui::GetForegroundDrawList()->AddText(
        pos, 
        ImGui::ColorConvertFloat4ToU32(GetFrameTimeColor(frame_time)), 
        frame_time_str
    );
}

void FPSModule::ProcessHotkeys() {
    if (KeyBinds::IsKeyPressed(toggle_key)) {
        show_fps = !show_fps;
        SetEnabled(show_fps);
    }
}

void FPSModule::LoadConfig() {
    // Load configuration from file or registry
    // For now, use default values
}

void FPSModule::SaveConfig() {
    // Save configuration to file or registry
}

ImVec4 FPSModule::GetFPSColor(float fps) const {
    if (fps >= 60.0f) {
        return ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Green
    } else if (fps >= 30.0f) {
        return ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow
    } else {
        return ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red
    }
}

ImVec4 FPSModule::GetFrameTimeColor(float frame_time) const {
    if (frame_time <= 16.67f) { // 60+ FPS
        return ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Green
    } else if (frame_time <= 33.33f) { // 30+ FPS
        return ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow
    } else {
        return ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red
    }
}