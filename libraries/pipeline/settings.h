#pragma once

#include "keybinds.h"

class Settings {
public:
#pragma region MenuStatus
	KeyBinds::Config KeyBinds = {
		VK_F12 // toggle menu
	};

	bool ImGuiInitialized = false;
	bool bShowMenu = true;
	bool show_console = true;
	
private:
	
	 
};

extern Settings settings;