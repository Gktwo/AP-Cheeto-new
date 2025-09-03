#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/AboutTAB.h"
#include "pipeline/gui/GUITheme.h" 
//#include "pipeline/settings.h"
#include "main.h"
#include <iostream>



bool toggle = false;

void AboutTAB::Render() {
	if (ImGui::BeginTabItem("About")) {

		ImGui::Spacing();
		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 550.0f);
		ImGui::PopTextWrapPos();
		ImGui::Text( "Game: AzurPromilia cbt1 ");
		ImGui::Text("Version: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "0.0.9");
		ImGui::Text("Author: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "gktwo");
		ImGui::Text("GitHub: ");
		ImGui::SameLine();
		TextURL("AP-Cheeto-new", "https://github.com/Gktwo/AP-Cheeto-new");
		//ToggleSwitch("测试切换", &toggle);
		//HelperMarker("这是一个测试切换开关");
		ImGui::EndTabItem();
	}
}

