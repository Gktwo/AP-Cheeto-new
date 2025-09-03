#include "pch-il2cpp.h"
#include "FpsUnlocker.h"
#include "../keybinds.h"
#include "imgui/imgui.h"
#include <iostream>

FpsUnlocker::FpsUnlocker() : BaseModule("Fps Unlocker") {
    Unlimited = false;
	fpsvalue = 60;
}

void FpsUnlocker::Initialize() {
    // std::cout << "[INFO] FPS Module initialized" << std::endl;
    LoadConfig();
}

void FpsUnlocker::Shutdown() {
    SaveConfig();
    std::cout << "[INFO] FPS Module shutdown" << std::endl;
}

void FpsUnlocker::OnUpdate() {
    // Synchronization is now automatic
}

void FpsUnlocker::RenderGUI() {
    if (ImGui::CollapsingHeader("Fps Unlocker")) {
        ImGui::Indent();
        if (
            //ImGui::Checkbox("Show FPS Overlay", &enabled)
            ToggleSwitch("Fps Unlocker Enabled", &enabled)
            ) {
            if (enabled) {
                EnableFpsUnlocker();
                
            }
            else {
                DisableFpsUnlocker();
                
			}
            // enabled state is directly managed by BaseModule
        }
        if (enabled) {
            ImGui::Indent();
            if (ImGui::DragInt("Fps Value", &fpsvalue, 1, -1, 500))
                Unlimited = false;
			
            if (ToggleSwitch("Unlimited", &Unlimited)) {
                if (Unlimited)
                    fpsvalue = -1;
                else
                    fpsvalue = 60;
            }
            ImGui::Unindent();
        }

            
        ImGui::Unindent();
    }
}

void FpsUnlocker::RenderOverlay() {

}

void FpsUnlocker::ProcessHotkeys() {
    //if (KeyBinds::IsKeyPressed(toggle_key)) {
    //    enabled = !enabled;
    //    // enabled state is directly managed by BaseModule
    //}
}

void FpsUnlocker::EnableFpsUnlocker() {
    HookManager::install(app::AzurWorld_OnUpdate, AzurWorld_OnUpdate_fpsunlocker_Hook);
}

void FpsUnlocker::DisableFpsUnlocker() {
    app::Application_set_targetFrameRate(60, nullptr);
    HookManager::detach(AzurWorld_OnUpdate_fpsunlocker_Hook);
}

void FpsUnlocker::AzurWorld_OnUpdate_fpsunlocker_Hook(app::AzurWorld* __this, MethodInfo* method) {
    FpsUnlocker& instance = FpsUnlocker::GetInstance();
    if (instance.enabled&&app::Application_get_isFocused(nullptr)) {
        app::Application_set_targetFrameRate(instance.fpsvalue, nullptr);
    }
    CALL_ORIGIN(AzurWorld_OnUpdate_fpsunlocker_Hook, __this, method);
}