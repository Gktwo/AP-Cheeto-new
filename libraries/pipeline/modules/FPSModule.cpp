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
}

void FPSModule::RenderGUI() {
    if (ImGui::CollapsingHeader("FPS Monitor")) {
        ImGui::Indent();
        if (ImGui::Checkbox("Show FPS Overlay", &show_fps)) {
            SetEnabled(show_fps);
        }
        ImGui::Text("Toggle Key: %s", KeyBinds::ToString(toggle_key));
        ImGui::SameLine();
        if (ImGui::Button("Change##fps_key")) {
        }
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
    ImVec2 pos(10.0f, 10.0f);
    ImGui::GetForegroundDrawList()->AddText(
        pos, 
        ImGui::ColorConvertFloat4ToU32(GetFPSColor(fps)), 
        ("FPS: " + std::to_string((int)fps)).c_str()
    );
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
}

void FPSModule::SaveConfig() {
}

ImVec4 FPSModule::GetFPSColor(float fps) const {
    if (fps >= 60.0f) {
        return ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    } else if (fps >= 30.0f) {
        return ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    } else {
        return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
}

ImVec4 FPSModule::GetFrameTimeColor(float frame_time) const {
    if (frame_time <= 16.67f) {
        return ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    } else if (frame_time <= 33.33f) {
        return ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    } else {
        return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
}