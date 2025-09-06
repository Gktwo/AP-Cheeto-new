#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/SettingsTAB.h"
#include "pipeline/settings.h"
#include "../../modules//UnityExplorerModule.h"

void SettingsTAB::Render()
{
	if (ImGui::BeginTabItem("Settings")) {
		ImGui::Spacing();

		//ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.8f, 1.0f), "General Settings");
		//ImGui::Separator();
		//ImGui::Spacing();
		//
		//ImGui::Text("Application settings will be added here.");
		if (ToggleSwitch("Toggle Console", &settings.show_console)) {
			ToggleConsole(settings.show_console);
			LOG_INFO("Console {}", settings.show_console ? "Enabled" : "Disabled");
		}
		UnityExplorerModule::GetInstance().RenderGUI();
		if (ImGui::Button("uid")) {
			app::GameObject* uid = app::GameObject_Find(string_to_il2cppi_app("/[UI Root]/[VisiableWaterMark]/testingWaterMark/markIdText"), nullptr);
			printf(il2cppi_to_string(app::Object_1_GetName(RCAST(app::Object_1*, uid), nullptr)).c_str());
			app::Component* LText_comp = app::GameObject_GetComponentByName(uid, string_to_il2cppi_app("LTextMeshProUGUI, Assembly-CSharp"), nullptr);
			if (LText_comp != nullptr) {
				printf("%s\n", il2cppi_to_string( app::LTextMeshProUGUI_get_text(RCAST(app::LTextMeshProUGUI*, LText_comp), nullptr)).c_str());
			
			}
				//app::LTextMeshProUGUI_set_text(RCAST(app::LTextMeshProUGUI*, LText_comp), string_to_il2cppi_app("<color=red>test UID</color>"), nullptr);
		}


		
		ImGui::EndTabItem();
	}
}

void SettingsTAB::ToggleConsole(BOOL show)
{
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL)
	{
		ShowWindow(hwnd, show ? SW_SHOW : SW_HIDE);
	}
}