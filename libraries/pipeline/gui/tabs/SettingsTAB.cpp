#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/SettingsTAB.h"

void SettingsTAB::Render()
{
	if (ImGui::BeginTabItem("Settings")) {
		ImGui::Spacing();
		
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.8f, 1.0f), "General Settings");
		ImGui::Separator();
		ImGui::Spacing();
		
		ImGui::Text("Application settings will be added here.");

		ImGui::EndTabItem();
	}
}