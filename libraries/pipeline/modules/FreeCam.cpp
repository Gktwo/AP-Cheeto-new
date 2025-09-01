#include "pch-il2cpp.h"
#include "FreeCam.h"
#include "../keybinds.h"
#include "imgui/imgui.h"
#include <iostream>

FreeCam::FreeCam() : BaseModule("FPS Monitor"),
 /*toggle_key(VK_F5),*/
	f_Forward('W'),
	f_Backward('S'),
	f_Left('A'),
	f_Right('D'),
	f_Up(VK_SPACE),
	f_Down(VK_LCONTROL),
	f_IncFOV(VK_ADD),
	f_DecFOV(VK_SUBTRACT),
	f_LeftRoll(VK_LEFT),
	f_RightRoll(VK_RIGHT),
	f_ResetRoll(VK_NUMPAD0),
	MoveSpeed(1.0f),
	LookSens(1.0f),
	RollSpeed(1.0f),
	FOVSpeed(0.1f),
	FOV(45.0f),
	MovSmoothing(1.0f),
	LookSmoothing(1.0f),
	RollSmoothing(1.0f),
	FovSmoothing(1.0f)
{
	enabled = false; 

	app::GameObject* freeCam = nullptr;
	app::GameObject* mainCam = nullptr;
	app::Object_1* freeCamObj = nullptr;
	//app::Object_1* mainCamObj = nullptr;

	app::Transform* freeCam_Transform = nullptr;
	app::Component* freeCam_Camera = nullptr;
	app::Component* mainCam_Camera = nullptr;
	app::Vector3 targetPosition;
	app::Vector3 smoothPosition;
	float smoothFOV = 0;
	double focalLength = 0;
	bool FCamisEnabled = false;
}

void FreeCam::Initialize() {
	std::cout << "[INFO] FPS Module initialized" << std::endl;

}

void FreeCam::Shutdown() {

	std::cout << "[INFO] FPS Module shutdown" << std::endl;
}

void FreeCam::OnUpdate() {

}

void FreeCam::RenderGUI() {
	if (ImGui::CollapsingHeader("Free Camera")) {
		ImGui::Indent();
		if (ImGui::Checkbox("On/Off", &enabled)) {
			// enabled state is directly managed by BaseModule
		}
		if (enabled) {
			ImGui::DragFloat("Move Speed", &MoveSpeed, 1.0f, 0.1f, 30.0f);
			ImGui::DragFloat("Look Sensitivity", &LookSens, 1.0f, 0.1f, 100.0f);
			ImGui::DragFloat("Roll Speed", &RollSpeed, 1.0f, 0.1f, 100.0f);
			ImGui::DragFloat("FOV Speed", &FOVSpeed, 1.0f, 0.1f, 100.0f);
			ImGui::InputFloat("FOV", &FOV, 1.0f, 1.0f, "%.1f");
			//ImGui::SameLine();
			ImGui::Separator();
			ImGui::Text("Forward Key: %s", KeyBinds::ToString(f_Forward)); ImGui::SameLine();
			ImGui::Text("Backward Key: %s", KeyBinds::ToString(f_Backward));
			ImGui::Text("Left Key: %s", KeyBinds::ToString(f_Left)); ImGui::SameLine();
			ImGui::Text("Right Key: %s", KeyBinds::ToString(f_Right));
			ImGui::Text("Up Key: %s", KeyBinds::ToString(f_Up)); ImGui::SameLine();
			ImGui::Text("Down Key: %s", KeyBinds::ToString(f_Down));
			ImGui::Text("IncFOV Key: %s", KeyBinds::ToString(f_IncFOV)); ImGui::SameLine();
			ImGui::Text("DecFOV Key: %s", KeyBinds::ToString(f_DecFOV));
			ImGui::Text("LeftRoll Key: %s", KeyBinds::ToString(f_LeftRoll)); ImGui::SameLine();
			ImGui::Text("RightRoll Key: %s", KeyBinds::ToString(f_RightRoll));
			ImGui::Text("ResetRoll Key: %s", KeyBinds::ToString(f_ResetRoll));

		}
		ImGui::Unindent();

	}
}

void FreeCam::RenderOverlay() {}



void FreeCam::ProcessHotkeys() {}





