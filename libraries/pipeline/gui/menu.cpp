#include "pch-il2cpp.h"
#include "menu.h"
#include "imgui/imgui.h"

#include "pipeline/settings.h"
#include "pipeline/gui/tabs/AboutTAB.h"
#include "pipeline/gui/tabs/SettingsTAB.h"
#include "pipeline/gui/tabs/PlayTAB.h"
#include "pipeline/gui/tabs/ESPTAB.h"
#include "pipeline/gui/tabs/WorldTAB.h"
#include "pipeline/gui/tabs/VisualTAB.h"




namespace Menu {
	bool init = false;
	bool firstRender = true;

	void Init() {
		ImGui::SetNextWindowBgAlpha(0.7f);
		ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
		init = true;
	}

	void Render() {
		if (!init)
			Menu::Init();

		ImGui::Begin("AP - Cheeto           Press F12 to show panel", &settings.bShowMenu, ImGuiWindowFlags_NoCollapse);
		ImGui::BeginTabBar("#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		if (firstRender) {
			firstRender = false;
		}
		else {
			AboutTAB::Render();
			PlayTAB::Render();
			ESPTAB::Render();
			WorldTAB::Render();
			VisualTAB::Render();
			SettingsTAB::Render();
		}

		ImGui::EndTabBar();
		ImGui::End();



	}
}