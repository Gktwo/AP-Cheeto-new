#include "pch-il2cpp.h"
#include "ESPModule.h"
#include "../keybinds.h"
#include "main.h"
#include <iostream>


ESPModule::ESPModule() : BaseModule("ESP"), toggle_key(VK_F6) {
    // enabled is inherited from BaseModule and defaults to false
    red = ImColor(255, 0, 0);
    orange = ImColor(255, 165, 0);
    yellow = ImColor(255, 255, 0);
    green = ImColor(0, 255, 0);
    blue = ImColor(0, 0, 255);
    qing = ImColor(0, 255, 255);
    purple = ImColor(148, 0, 211);
    white = ImColor(255, 255, 255);
    deeppink = ImColor(255, 20, 147);
    pink = ImColor(255, 192, 203);
    black = ImColor(0, 0, 0);
    gray = ImColor(128, 128, 128);
    show_monster = true;
    show_npc = true;
    show_friendly = true;
    show_puzzle = true;
    show_all = false;
    show_distance = true;
    show_configid = false;
    show_configname = true;
    show_entityid = false;
    show_type = false;
}

void ESPModule::Initialize() {
   // std::cout << "[INFO] ESP Module initialized" << std::endl;
    LoadConfig();
}

void ESPModule::Shutdown() {
    SaveConfig();
    std::cout << "[INFO] ESP Module shutdown" << std::endl;
}

void ESPModule::OnUpdate() {
}

void ESPModule::RenderGUI() {
    if (ImGui::CollapsingHeader("ESP Features")) {
        ImGui::Indent();
        ImGui::Checkbox("ESP Enabled", &enabled);
        ImGui::Text("Toggle Key: %s", KeyBinds::ToString(toggle_key));
        ImGui::SameLine();
        if (ImGui::Button("Change##esp_key")) {
        }
        if (enabled) {
            ImGui::Spacing();
            if (ImGui::TreeNode("Display Types")) {
                ImGui::Checkbox("Show Monsters", &show_monster);
                ImGui::SameLine();
                ImGui::Checkbox("Show NPCs", &show_npc);
                ImGui::SameLine();
                ImGui::Checkbox("Show Friendly", &show_friendly);
                ImGui::Checkbox("Show Puzzles", &show_puzzle);
                ImGui::SameLine();
                ImGui::Checkbox("Show All", &show_all);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Display Info")) {
                ImGui::Checkbox("Show Distance", &show_distance);
                ImGui::SameLine();
                ImGui::Checkbox("Show Config ID", &show_configid);
                ImGui::SameLine();
                ImGui::Checkbox("Show Config Name", &show_configname);
                ImGui::Checkbox("Show Entity ID", &show_entityid);
                ImGui::SameLine();
                ImGui::Checkbox("Show Type", &show_type);
                ImGui::TreePop();
            }
        }
        ImGui::Unindent();
    }
}

void ESPModule::RenderOverlay() {
    if (!enabled) return;
    drawESP();
}

void ESPModule::ProcessHotkeys() {
    if (KeyBinds::IsKeyPressed(toggle_key)) {
        enabled = !enabled;
    }
}



void ESPModule::drawESP() {
    app::List_1_Lens_Gameplay_Modules_BigWorld_Entity_* entityList = app::EntityManager_GetAllEntities(nullptr);
    if (entityList == nullptr) return;
    app::Entity__Array* EN_AR = entityList->fields._items;
    int count = entityList->fields._size;
    auto playerPos = app::PlayerManager_GetMainPlayerPosition(app::AzurWorld_get_playerMgr(nullptr), nullptr);
    for (size_t i = 0; i < count; i++) {
        app::Entity* entity = EN_AR->vector[i];
        if (entity == nullptr) continue;
        app::BaseData* data = entity->fields.data;
        if (data == nullptr) continue;
        app::EEntityType__Enum entityType = app::BaseData_get_entityType(data, nullptr);
        EntityDisplayInfo displayInfo = getEntityDisplayInfo(entityType);
        if (!displayInfo.shouldShow) continue;
        auto screenWidth = app::Screen_get_width(nullptr);
        auto screenHeight = app::Screen_get_height(nullptr);
        app::Vector3 pos = app::BaseData_GetPosition(data, nullptr);
        float distance = app::Vector3_Distance(playerPos, pos, nullptr);
        if (distance > 300.f) continue;
        app::Vector3 rect = app::Camera_WorldToScreenPoint_1(app::Camera_get_main(nullptr), pos, nullptr);
        if (rect.z < 0.1f) continue;
        std::string showtext = "";
        if (show_distance) {
            addtext(showtext, (std::to_string((int)distance) + "m"), true);
        }
        if (show_configid) {
            int id = app::BaseData_get_configId(data, nullptr);
            addtext(showtext, std::to_string(id));
        }
        if (show_configname) {
            std::string nameStr = "unknown";
            app::String* name = app::BaseData_get_configName(data, nullptr);
            if (name != nullptr)
                nameStr = il2cppi_to_string(name);
            addtext(showtext, nameStr);
        }
        if (show_entityid) {
            uint32_t entityId = app::BaseData_get_entityId(data, nullptr);
            addtext(showtext, std::to_string(entityId));
        }
        if (show_type) {
            std::string typeStr = std::string(magic_enum::enum_name(entityType));
            addtext(showtext, typeStr);
        }
        if (showtext.empty()) continue;
        ImVec2 imguiPos(rect.x, screenHeight - rect.y);
        ImGui::PushFont(ImGui::GetIO().FontDefault);
        ImGui::GetForegroundDrawList()->AddText(nullptr, 18.0f, imguiPos, displayInfo.color, showtext.c_str());
        ImGui::PopFont();
        ImGui::GetForegroundDrawList()->AddLine(ImVec2(screenWidth / 2, 0), imguiPos, displayInfo.color, 1.0f);
    }
}

EntityDisplayInfo ESPModule::getEntityDisplayInfo(app::EEntityType__Enum type) {
    EntityDisplayInfo info;
    switch (type) {
    case app::EEntityType__Enum::Boss:
    case app::EEntityType__Enum::Monster:
        info.color = red;
        info.shouldShow = show_all || show_monster;
        break;
    case app::EEntityType__Enum::NPC:
        info.color = blue;
        info.shouldShow = show_all || show_npc;
        break;
    case app::EEntityType__Enum::Player:
    case app::EEntityType__Enum::Pet:
    case app::EEntityType__Enum::HomePet:
    case app::EEntityType__Enum::BigWorldPet:
    case app::EEntityType__Enum::Hero:
        info.color = green;
        info.shouldShow = show_all || show_friendly;
        break;
    case app::EEntityType__Enum::PuzzleItem:
    case app::EEntityType__Enum::BreakableItem:
        info.color = orange;
        info.shouldShow = show_all || show_puzzle;
        break;
    default:
        info.color = white;
        info.shouldShow = show_all;
        break;
    }
    return info;
}

std::string ESPModule::addtext(std::string& text, const std::string& newtext, bool first) {
    if (!first && !text.empty()) {
        text += " | ";
    }
    text += newtext;
    return text;
}