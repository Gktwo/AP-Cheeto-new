#pragma once
#include "../libraries/imgui/imgui.h"


// 内联 Toggle Switch (滑块样式)
inline bool ToggleSwitch(const char* label, bool* v)
{
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	ImVec2 p = ImGui::GetCursorScreenPos();
	float w = 40.0f, h = 20.0f;
	ImVec2 size(w, h);

	// InvisibleButton：保证点击区域
	ImGui::InvisibleButton(label, size);
	bool clicked = ImGui::IsItemClicked();
	if (clicked)
		*v = !*v;

	// 背景颜色：true=绿色，false=红色
	ImU32 col_bg = *v ? IM_COL32(100, 200, 100, 255)
		: IM_COL32(200, 80, 80, 255);
	ImU32 col_knob = IM_COL32(255, 255, 255, 255);

	float radius = h * 0.5f;
	draw_list->AddRectFilled(p, ImVec2(p.x + w, p.y + h), col_bg, radius);

	float t = *v ? 1.0f : 0.0f;
	float knob_x = p.x + radius + t * (w - h);
	float knob_y = p.y + radius;
	draw_list->AddCircleFilled(ImVec2(knob_x, knob_y), radius * 0.8f, col_knob);

	// ----------- 文字居中对齐 -----------
	// Check if label should be hidden (starts with ##)
	const char* display_label = label;
	if (label[0] == '#' && label[1] == '#') {
		// Skip rendering text for hidden labels
	} else {
		ImGui::SameLine();
		ImVec2 text_size = ImGui::CalcTextSize(label);
		ImGui::SetCursorScreenPos(ImVec2(
			p.x + w + 6,                       // 开关右边间距
			p.y + (h - text_size.y) * 0.5f     // 居中
		));
		ImGui::TextUnformatted(label);
	}

	return clicked;
}



inline void HelperMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f); // 自动换行宽度
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

inline void TextURL(
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
		ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
	}
}