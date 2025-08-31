#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/AboutTAB.h"
#include "pipeline/gui/GUITheme.h" 
//#include "pipeline/settings.h"
#include "main.h"
#include <iostream>
#include <shellapi.h>



void AboutTAB::Render() {
	if (ImGui::BeginTabItem("About")) {

		ImGui::Spacing();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Game: AzurPromilia ");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Version: 0.0.9");
		ImGui::Spacing();
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Author: GKTWO");
		ImGui::Text("GitHub: ");
		ImGui::SameLine();
		ImGui::TextURL("https://github.com/GKTWO", "https://github.com/GKTWO", true);


		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 550.0f);
		ImGui::PopTextWrapPos();





	

		ImGui::EndTabItem();
	}
}


