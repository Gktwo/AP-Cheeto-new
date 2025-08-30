#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/SettingsTAB.h"
#include <imgui/imgui.h>
#include "pipeline/gui/GUITheme.h" 
#include "pipeline/settings.h"
#include "main.h"
#include <iostream>
bool SettingsTAB::esp_enabled = false;
void SettingsTAB::Render()
{
    if (ImGui::BeginTabItem("Settings")) {

        ImGui::Spacing();

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Version: 0.0.9");
        ImGui::Spacing();

        ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 550.0f);
        ImGui::PopTextWrapPos();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        
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
        ImGui::Checkbox("ESP", &esp_enabled);

        ImGui::EndTabItem();
    }
}
ImColor red = ImColor(255, 0, 0);
void SettingsTAB::drawESP() {
    app::List_1_Lens_Gameplay_Modules_BigWorld_Entity_* entityList = app::EntityManager_GetAllEntities(nullptr);
    if (entityList == nullptr)return;
    app::Entity__Array* EN_AR = entityList->fields._items;
    int count = entityList->fields._size;
    //std::cout << "Entity Count: " << count << std::endl;
    auto playerPos = app::PlayerManager_GetMainPlayerPosition(app::AzurWorld_get_playerMgr(nullptr), nullptr);
    for (size_t i = 0; i < count; i++)
    {
        app::Entity* entity = EN_AR->vector[i];

        if (entity == nullptr)continue;

        //std::cout << "not found getconfigname "  << std::endl;
        app::BaseData* data = entity->fields.data;
        auto screenWidth = app::Screen_get_width(nullptr);
        auto screenHeight = app::Screen_get_height(nullptr);
        app::Vector3 pos = app::BaseData_GetPosition(data, nullptr);
        float distance = app::Vector3_Distance(playerPos, pos, nullptr);
        if (distance > 300.f) continue;

        app::Vector3 rect = app::Camera_WorldToScreenPoint_1(app::Camera_get_main(nullptr), pos, nullptr);
        if (rect.z < 0.1f) continue;
        std::string showtext = "";

        addtext(showtext, (std::to_string(distance)+"m"), true);

        int id = app::BaseData_get_configId(data, nullptr);
        addtext(showtext, std::to_string(id));

        std::string nameStr = "known";
        app::String* name = app::BaseData_get_configName(data, nullptr);
        if (name != nullptr)
            nameStr = il2cppi_to_string(name);
        addtext(showtext,nameStr);
        

        //std::cout << "Entity [" << i << "] configid: " << id << "  name:" << nameStr << std::endl;
  
        





        ImVec2 imguiPos(rect.x, screenHeight - rect.y);
        



        ImGui::PushFont(ImGui::GetIO().FontDefault);
        ImGui::GetForegroundDrawList()->AddText(nullptr, 18.0f, imguiPos, red, showtext.c_str());
        ImGui::PopFont();

        // 绘制连线
        ImGui::GetForegroundDrawList()->AddLine(ImVec2(screenWidth / 2, 0), imguiPos, red, 1.0f);

    }

}
std::string SettingsTAB::addtext(std::string& text, std::string newtext, bool first) {
    
    if (text.empty()&&!first)
        return text;
    text += " | ";
    text += newtext;
    return text;
}