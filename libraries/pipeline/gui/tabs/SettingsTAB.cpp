#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/SettingsTAB.h"
#include "pipeline/settings.h"



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
		if (ImGui::Button("objs")) {
			printf("中文\n");
			app::Scene__Array* scenes = app::SceneManager_GetAllScenes(nullptr);
			int numScenes = scenes->max_length;
			//auto scenes_ = scenes->vector;
			
			printf("get scenes size : %d\n", numScenes);
			for (int i = 0; i < numScenes; i++) {
				app::Scene scene = scenes->vector[i];
				std::string name = il2cppi_to_string(app::Scene_get_name(&scene, nullptr));
				printf("scene [%d] : %s  \n", i, name.c_str());
				app::GameObject__Array* objs = app::Scene_GetRootGameObjects(&scene, nullptr);
				int numObjs = objs->max_length;
				for (int j = 0; j < numObjs; j++)
				{
					app::GameObject* obj = objs->vector[j];
					std::string objname = il2cppi_to_string(app::Object_1_GetName(RCAST(app::Object_1*, obj),nullptr));
					printf("gameobj[%d] :%s\n",j, objname.c_str());
					app::Transform* trans = app::GameObject_get_transform(obj, nullptr);
					int childCount = app::Transform_get_childCount(trans, nullptr);
					for (int k = 0; k < childCount; k++) {
						app::Transform* child = app::Transform_GetChild(trans, k ,nullptr);
						app::GameObject* childObj = app::Component_get_gameObject(RCAST(app::Component*, child), nullptr);
						std::string objname_ = il2cppi_to_string(app::Object_1_GetName(RCAST(app::Object_1*, childObj), nullptr));
						printf("    gameobj[%d] :%s\n", j, objname_.c_str());
					}
					


				}
			}
			
			
		
		
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