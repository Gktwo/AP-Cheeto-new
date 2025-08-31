#pragma once
#include "pch-il2cpp.h"

// Entity display info structure
struct EntityDisplayInfo {
	bool shouldShow;
	ImColor color;
};

namespace ESPTAB {
	void Render();
	extern bool esp_enabled;
	
	// Display type control variables
	extern bool show_monster;
	extern bool show_npc;
	extern bool show_friendly;
	extern bool show_puzzle;
	extern bool show_all;
	
	// Display info control variables
	extern bool show_distance;
	extern bool show_configid;
	extern bool show_configname;
	extern bool show_entityid;
	extern bool show_type;
	
	void drawESP();
	std::string addtext(std::string& text, std::string newtext, bool first);
	std::string addtext(std::string& text, std::string newtext);
	EntityDisplayInfo getEntityDisplayInfo(app::EEntityType__Enum type);
	
	// Color definitions
	extern ImColor red;
	extern ImColor blue;
	extern ImColor green;
	extern ImColor orange;
	extern ImColor white;
}