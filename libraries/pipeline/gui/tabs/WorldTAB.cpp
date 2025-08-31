#include "pch-il2cpp.h"
#include "WorldTAB.h"
#include <imgui/imgui.h>
#include "pipeline/HookManager.h"
#include <iostream>

bool world_speed_enabled = false;
float world_speed_value = 1.0f;
void AzurWorld_OnUpdate_world_speed_Hook(app::AzurWorld* __this, MethodInfo* method);


void WorldTAB::Render() {
    if (ImGui::BeginTabItem("World")) {
        ImGui::Spacing();
        
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.5f, 1.0f), "World Features");
        ImGui::Separator();
        ImGui::Spacing();

        // 空的UI界面
        if(ImGui::Checkbox("World Speed", &world_speed_enabled))
        {

            if(world_speed_enabled)
            {
                HookManager::install(app::AzurWorld_OnUpdate, AzurWorld_OnUpdate_world_speed_Hook);
                // 这里可以添加启用世界加速的逻辑
            }
            else
            {
                app::Time_1_set_timeScale(1.0f, nullptr);
				HookManager::detach(AzurWorld_OnUpdate_world_speed_Hook);
			}
        }
        ImGui::SameLine();
        if (ImGui::Button("reset")) { world_speed_value = 1.f; }
        if(world_speed_enabled)
        {
            ImGui::Indent();
            ImGui::SliderFloat("Speed valuer", &world_speed_value, 0.1f, 20.f, "%.1f");
            ImGui::Unindent();
		}
       
        
        ImGui::EndTabItem();
    }
}


void AzurWorld_OnUpdate_world_speed_Hook(app::AzurWorld* __this, MethodInfo* method) {

    if(world_speed_enabled)
    {
		app::Time_1_set_timeScale(world_speed_value, nullptr);
	}
	CALL_ORIGIN(AzurWorld_OnUpdate_world_speed_Hook, __this, method);

}

