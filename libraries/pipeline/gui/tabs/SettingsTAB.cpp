#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/SettingsTAB.h"
#include "pipeline/gui/GUITheme.h" 
#include "pipeline/settings.h"
#include "main.h"
#include <iostream>



// Settings variables can be added here


void SettingsTAB::Render()
{
	if (ImGui::BeginTabItem("Settings")) {


		ImGui::Spacing();

		//if (ImGui::Button("Unhook"))
		//{
		//    SetEvent(hUnloadEvent);
		//}

  //      if(ImGui::Button("get entitys"))
  //      {
  //          
  //          
		//}
		
		ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.5f, 1.0f), "General Settings");
		ImGui::Separator();
		ImGui::Spacing();
		
		// General settings can be added here
		ImGui::Text("Settings functionality under development...");

		ImGui::EndTabItem();
	}
}

// ESP functionality has been moved to ESPTAB