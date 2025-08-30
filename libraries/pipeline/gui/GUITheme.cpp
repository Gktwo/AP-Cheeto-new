#include "pch-il2cpp.h"

#include "pipeline/gui/GUITheme.h"
#include "pipeline/settings.h"
#include <imgui/imgui.h>

void ApplyTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.07f, 0.90f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.07f, 0.90f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.10f, 0.10f, 0.12f, 0.95f);

    colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.25f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

    colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.12f, 0.85f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.15f, 0.15f, 0.18f, 0.85f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.20f, 0.24f, 0.85f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.07f, 0.07f, 0.09f, 0.85f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.10f, 0.12f, 0.95f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.05f, 0.07f, 0.80f);

    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.60f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.35f, 0.80f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.35f, 0.35f, 0.40f, 0.90f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.40f, 0.40f, 0.45f, 1.00f);

    colors[ImGuiCol_CheckMark] = ImVec4(0.70f, 0.70f, 0.75f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.30f, 0.35f, 0.80f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.35f, 0.35f, 0.40f, 1.00f);

    colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.12f, 0.80f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.15f, 0.15f, 0.18f, 0.85f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.20f, 0.24f, 0.90f);

    colors[ImGuiCol_Header] = ImVec4(0.12f, 0.12f, 0.15f, 0.80f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.17f, 0.17f, 0.20f, 0.85f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.22f, 0.22f, 0.26f, 0.90f);

    colors[ImGuiCol_Separator] = ImVec4(0.15f, 0.15f, 0.18f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.20f, 0.20f, 0.24f, 0.75f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.25f, 0.25f, 0.30f, 1.00f);

    colors[ImGuiCol_ResizeGrip] = ImVec4(0.30f, 0.30f, 0.35f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.35f, 0.35f, 0.40f, 0.50f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.40f, 0.45f, 0.70f);

    colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.10f, 0.12f, 0.80f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.15f, 0.15f, 0.18f, 0.85f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.24f, 0.90f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.07f, 0.09f, 0.70f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.12f, 0.12f, 0.15f, 0.80f);

    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.05f, 0.05f, 0.07f, 0.73f);

    style.WindowRounding = 8.0f;
    style.ChildRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 4.0f;

    style.WindowPadding = ImVec2(10, 10);
    style.FramePadding = ImVec2(8, 6);
    style.ItemSpacing = ImVec2(8, 8);
    style.ItemInnerSpacing = ImVec2(6, 6);
    style.IndentSpacing = 21.0f;

    style.ScrollbarSize = 15.0f;
    style.GrabMinSize = 10.0f;
}
