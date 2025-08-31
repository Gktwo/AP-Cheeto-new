#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/AboutTAB.h"
#include "pipeline/gui/GUITheme.h" 
//#include "pipeline/settings.h"
#include "main.h"
#include <iostream>
#include <shellapi.h>

static void TextURL(
	const char* label,
	const char* url,
	const ImVec4& color = ImVec4(0.0f, 0.5f, 1.0f, 1.0f),
	const ImVec4& hoverColor = ImVec4(0.2f, 0.7f, 1.0f, 1.0f))
{
	ImGui::PushStyleColor(ImGuiCol_Text, color);
	ImGui::TextUnformatted(label);
	ImGui::PopStyleColor();
	ImVec2 min = ImGui::GetItemRectMin();
	ImVec2 max = ImGui::GetItemRectMax();
	bool hovered = ImGui::IsItemHovered();

	if (hovered)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, hoverColor);
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		ImGui::SetTooltip("%s", url);
	}
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	draw_list->AddLine(
		ImVec2(min.x, max.y),
		ImVec2(max.x, max.y),
		ImGui::ColorConvertFloat4ToU32(hovered ? hoverColor : color));
	if (hovered)
		ImGui::PopStyleColor();
	if (hovered && ImGui::IsItemClicked())
	{
#ifdef _WIN32
		ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
#elif __APPLE__
		std::string command = "open " + std::string(url);
		system(command.c_str());
#else
		std::string command = "xdg-open " + std::string(url);
		system(command.c_str());
#endif
	}
}


void AboutTAB::Render() {
	if (ImGui::BeginTabItem("About")) {

		ImGui::Spacing();
		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 550.0f);
		ImGui::PopTextWrapPos();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Game: AzurPromilia cbt1 ");
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Version: 0.0.9");
		ImGui::Text("Author: ");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "gktwo");
		ImGui::Text("GitHub: ");
		ImGui::SameLine();
		TextURL("AP-Cheeto-new", "https://github.com/Gktwo/AP-Cheeto-new");







		ImGui::EndTabItem();
	}
}

