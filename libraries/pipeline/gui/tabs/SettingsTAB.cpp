#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/SettingsTAB.h"
#include "pipeline/gui/GUITheme.h" 
#include "pipeline/settings.h"
#include "main.h"
#include <iostream>
ImColor red = ImColor(255, 0, 0);      // 红
ImColor orange = ImColor(255, 165, 0);    // 橙
ImColor yellow = ImColor(255, 255, 0);     // 黄
ImColor green = ImColor(0, 255, 0);    // 绿
ImColor blue = ImColor(0, 0, 255);      // 蓝
ImColor qing = ImColor(0, 255, 255);     // qing
ImColor purple = ImColor(148, 0, 211);     // 紫
ImColor white = ImColor(255, 255, 255);    // bai
ImColor deeppink = ImColor(255, 20, 147); //深粉色
ImColor pink = ImColor(255, 192, 203);//粉色se
ImColor black = ImColor(0, 0, 0);
ImColor gray = ImColor(128, 128, 128);


bool SettingsTAB::esp_enabled = false;

// Display type control variables
bool SettingsTAB::show_monster = true;
bool SettingsTAB::show_npc = true;
bool SettingsTAB::show_friendly = true;
bool SettingsTAB::show_puzzle = true;
bool SettingsTAB::show_all = false;

// Display info control variables
bool SettingsTAB::show_distance = true;
bool SettingsTAB::show_configid = false;
bool SettingsTAB::show_configname = true;
bool SettingsTAB::show_entityid = false;
bool SettingsTAB::show_type = false;


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
		ImGui::Checkbox("ESP", &esp_enabled);
		
		if (esp_enabled) {
			ImGui::Indent();
			
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
			
			ImGui::Unindent();
		}

		ImGui::EndTabItem();
	}
}

void SettingsTAB::drawESP() {
	app::List_1_Lens_Gameplay_Modules_BigWorld_Entity_* entityList = app::EntityManager_GetAllEntities(nullptr);
	if (entityList == nullptr)return;
	app::Entity__Array* EN_AR = entityList->fields._items;
	int count = entityList->fields._size;
	auto playerPos = app::PlayerManager_GetMainPlayerPosition(app::AzurWorld_get_playerMgr(nullptr), nullptr);
	
	for (size_t i = 0; i < count; i++)
	{
		app::Entity* entity = EN_AR->vector[i];
		if (entity == nullptr) continue;

		app::BaseData* data = entity->fields.data;
		if (data == nullptr) continue;
		
		// Get entity type and display info
		app::EEntityType__Enum entityType = app::BaseData_get_entityType(data, nullptr);
		EntityDisplayInfo displayInfo = getEntityDisplayInfo(entityType);
		
		// Check if this entity should be displayed
		if (!displayInfo.shouldShow) continue;

		auto screenWidth = app::Screen_get_width(nullptr);
		auto screenHeight = app::Screen_get_height(nullptr);
		app::Vector3 pos = app::BaseData_GetPosition(data, nullptr);
		float distance = app::Vector3_Distance(playerPos, pos, nullptr);
		if (distance > 300.f) continue;

		app::Vector3 rect = app::Camera_WorldToScreenPoint_1(app::Camera_get_main(nullptr), pos, nullptr);
		if (rect.z < 0.1f) continue;
		
		// Build display text
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
		
		// Skip if no content to display
		if (showtext.empty()) continue;

		ImVec2 imguiPos(rect.x, screenHeight - rect.y);

		ImGui::PushFont(ImGui::GetIO().FontDefault);
		ImGui::GetForegroundDrawList()->AddText(nullptr, 18.0f, imguiPos, displayInfo.color, showtext.c_str());
		ImGui::PopFont();

		// Draw connection line
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(screenWidth / 2, 0), imguiPos, displayInfo.color, 1.0f);
	}
}

EntityDisplayInfo SettingsTAB::getEntityDisplayInfo(app::EEntityType__Enum type) {
	EntityDisplayInfo info;
	
	// Determine color based on entity type
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
std::string SettingsTAB::addtext(std::string& text, std::string newtext, bool first) {
	if (!first && !text.empty()) {
		text += " | ";
	}
	text += newtext;
	return text;
}

std::string SettingsTAB::addtext(std::string& text, std::string newtext) {
	return addtext(text, newtext, false);
}