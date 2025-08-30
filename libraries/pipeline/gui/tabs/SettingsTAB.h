#pragma once

namespace SettingsTAB {
	void Render();
	extern bool esp_enabled;
	void drawESP();
	std::string addtext(std::string& text, std::string newtext, bool first = false);

}