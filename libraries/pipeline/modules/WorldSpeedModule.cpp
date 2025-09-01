#include "pch-il2cpp.h"
#include "WorldSpeedModule.h"
#include "../keybinds.h"
#include "pipeline/HookManager.h"
#include "imgui/imgui.h"
#include <iostream>

WorldSpeedModule::WorldSpeedModule()
	: BaseModule("World Speed"),
	world_speed_value(1.0f),
	toggle_key(VK_F7) {
	// enabled is inherited from BaseModule and defaults to false
}

void WorldSpeedModule::Initialize() {
	std::cout << "[INFO] World Speed Module initialized" << std::endl;
	LoadConfig();
}

void WorldSpeedModule::Shutdown() {
	if (enabled) {
		DisableWorldSpeed();
	}
	SaveConfig();
	std::cout << "[INFO] World Speed Module shutdown" << std::endl;
}

void WorldSpeedModule::OnUpdate() {
}

void WorldSpeedModule::RenderGUI() {
	if (ImGui::CollapsingHeader("World Speed")) {
		ImGui::Indent();
		if (ImGui::Checkbox("Enable World Speed", &enabled)) {
			if (enabled) {
				EnableWorldSpeed();
				std::cout << "[INFO] World Speed enabled with value: " << world_speed_value << std::endl;
			}
			else {
				DisableWorldSpeed();
				std::cout << "[INFO] World Speed disabled" << std::endl;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset")) {
			ResetSpeed();
		}
		if (enabled) {
			ImGui::Indent();
			ImGui::SliderFloat("Speed Value", &world_speed_value, 0.1f, 20.0f, "%.1f");
			ImGui::Unindent();
		}
		ImGui::Text("Toggle Key: %s", KeyBinds::ToString(toggle_key));
		ImGui::SameLine();
		if (ImGui::Button("Change##world_speed_key")) {
		}
		ImGui::Unindent();
	}
}

void WorldSpeedModule::RenderOverlay() {
}

void WorldSpeedModule::ProcessHotkeys() {
	if (KeyBinds::IsKeyPressed(toggle_key)) {
		enabled = !enabled;
		if (enabled) {
			EnableWorldSpeed();
		}
		else {
			DisableWorldSpeed();
		}
	}
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
	WorldSpeedModule& instance = WorldSpeedModule::GetInstance();
	if (instance.enabled) {
		app::Time_1_set_timeScale(instance.world_speed_value, nullptr);
	}
	CALL_ORIGIN(AzurWorld_OnUpdate_world_speed_Hook, __this, method);
}