#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/SettingsTAB.h"
#include "pipeline/gui/GUITheme.h" 
#include "pipeline/settings.h"
#include "main.h"
#include <iostream>


bool hookupdate = false;
// Settings variables can be added here
void AzurWorld_OnUpdate_Hook(app::AzurWorld* __this, MethodInfo* method);

void SettingsTAB::Render()
{
	if (ImGui::BeginTabItem("Settings")) {


		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.5f, 1.0f), "General Settings");
		ImGui::Separator();
		ImGui::Spacing();
		
		// General settings can be added here
		ImGui::Text("Settings functionality under development...");

		if (ImGui::Checkbox("try hook update",&hookupdate)) {
		
			HookManager::install(app::AzurWorld_OnUpdate, AzurWorld_OnUpdate_Hook);
		
		}

		ImGui::EndTabItem();
	}

	
}
void AzurWorld_OnUpdate_Hook(app::AzurWorld* __this, MethodInfo* method) {

	std::cout << "AzurWorld_OnUpdate_Hook" << std::endl;

	CALL_ORIGIN(AzurWorld_OnUpdate_Hook, __this, method);
}
// ESP functionality has been moved to ESPTAB