#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/SettingsTAB.h"
#include "pipeline/gui/GUITheme.h" 
#include "main.h"
#include <iostream>

bool showfps = true;
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

		ImGui::Checkbox("Show FPS Window", &showfps);

		if (ImGui::Checkbox("try hook update",&hookupdate)) {
			if(hookupdate)
			HookManager::install(app::AzurWorld_OnUpdate, AzurWorld_OnUpdate_Hook);
			else
			HookManager::detach(AzurWorld_OnUpdate_Hook);
		
		}

		ImGui::EndTabItem();
	}


}
void AzurWorld_OnUpdate_Hook(app::AzurWorld* __this, MethodInfo* method) {

	std::cout << "AzurWorld_OnUpdate_Hook" << std::endl;

	CALL_ORIGIN(AzurWorld_OnUpdate_Hook, __this, method);
}

void SettingsTAB::FPSRander() {
	if (!showfps) return;
	
	float fps = ImGui::GetIO().Framerate;
	float frameTime = 1000.0f / fps;
	
	// FPS color based on thresholds
	ImU32 fpsColor;
	if (fps >= 60.0f) {
		fpsColor = IM_COL32(0, 255, 0, 255); // Green for high FPS (>=60)
	} else if (fps >= 30.0f) {
		fpsColor = IM_COL32(255, 255, 0, 255); // Yellow for medium FPS (30-59)
	} else {
		fpsColor = IM_COL32(255, 0, 0, 255); // Red for low FPS (<30)
	}
	
	// Frame time color based on thresholds
	ImU32 frameTimeColor;
	if (frameTime <= 16.67f) {
		frameTimeColor = IM_COL32(0, 255, 0, 255); // Green for good frame time (<=16.67ms, 60fps+)
	} else if (frameTime <= 33.33f) {
		frameTimeColor = IM_COL32(255, 255, 0, 255); // Yellow for medium frame time (16.67-33.33ms, 30-60fps)
	} else {
		frameTimeColor = IM_COL32(255, 0, 0, 255); // Red for high frame time (>33.33ms, <30fps)
	}
	
	// Position FPS display at top-left corner
	ImVec2 fpsPos(10.0f, 10.0f);
	ImVec2 frameTimePos(10.0f, 35.0f);
	
	// Create FPS text
	char fpsText[64];
	snprintf(fpsText, sizeof(fpsText), "FPS: %.1f", fps);
	
	// Create frame time text
	char frameTimeText[64];
	snprintf(frameTimeText, sizeof(frameTimeText), "Frame Time: %.3f ms", frameTime);
	
	// Draw FPS text with color
	ImGui::GetForegroundDrawList()->AddText(nullptr, 18.0f, fpsPos, fpsColor, fpsText);
	
	// Draw frame time text with color
	ImGui::GetForegroundDrawList()->AddText(nullptr, 18.0f, frameTimePos, frameTimeColor, frameTimeText);
}

// ESP functionality has been moved to ESPTAB