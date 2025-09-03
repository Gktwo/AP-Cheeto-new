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