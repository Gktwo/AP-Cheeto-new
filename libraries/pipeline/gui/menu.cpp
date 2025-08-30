#include "pch-il2cpp.h"
#include "menu.h"
#include "imgui/imgui.h"

#include "pipeline/settings.h"
#include "pipeline/gui/tabs/SettingsTAB.h"

namespace Menu {
	bool init = false;
	bool firstRender = true;

	void Init() {
		ImGui::SetNextWindowBgAlpha(0.7f);
		ImGui::SetNextWindowSize(ImVec2(800, 600));
		init = true;
	}

	void Render() {
		if (!init)
			Menu::Init();

		ImGui::Begin("AP - Cheeto", &settings.bShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::BeginTabBar("TestGame#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		if (firstRender) {
			firstRender = false;
		}
		else {
			SettingsTAB::Render();
		}

		ImGui::EndTabBar();
		ImGui::End();
	}
}