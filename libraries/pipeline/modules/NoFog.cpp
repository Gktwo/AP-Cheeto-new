#include "pch-il2cpp.h"
#include "NoFog.h"
#include "../keybinds.h"
#include "pipeline/HookManager.h"
#include "imgui/imgui.h"
#include <iostream>

NoFog::NoFog()
	: BaseModule("No Fog")
{
	// enabled is inherited from BaseModule and defaults to false
}

void NoFog::Initialize() {
	//std::cout << "[INFO] No Fog Module initialized" << std::endl;
	LoadConfig();
}

void NoFog::Shutdown() {
	if (enabled) {
		DisableNoFog();
	}
	SaveConfig();
	std::cout << "[INFO] No Fog Module shutdown" << std::endl;
}

void NoFog::OnUpdate() {
}

void NoFog::RenderGUI() {
	if (ImGui::CollapsingHeader("No Fog")) {
		ImGui::Indent();
		if (ImGui::Checkbox("Enable No Fog", &enabled)) {
			if (enabled) {
				EnableNoFog();
				std::cout << "[INFO] No Fog enabled "  << std::endl;
			}
			else {
				DisableNoFog();
				std::cout << "[INFO] No Fog disabled" << std::endl;
			}
		}

		ImGui::Unindent();
	}
}

void NoFog::RenderOverlay() {
}

void NoFog::ProcessHotkeys() {

}


void NoFog::EnableNoFog() {
	HookManager::install(app::AzurWorld_OnUpdate, AzurWorld_OnUpdate_no_fog_Hook);
}

void NoFog::DisableNoFog() {
	app::RenderSettings_set_fog(true, nullptr);
	HookManager::detach(AzurWorld_OnUpdate_no_fog_Hook);
}



void NoFog::AzurWorld_OnUpdate_no_fog_Hook(app::AzurWorld* __this, MethodInfo* method) {
	NoFog& instance = NoFog::GetInstance();
	if (instance.enabled) {
		app::RenderSettings_set_fog(false, nullptr);
	}
	CALL_ORIGIN(AzurWorld_OnUpdate_no_fog_Hook, __this, method);
}