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


}

void FreeCam::Initialize() {
	//std::cout << "[INFO] FPS Module initialized" << std::endl;

}

void FreeCam::Shutdown() {

	std::cout << "[INFO] FPS Module shutdown" << std::endl;
}

void FreeCam::OnUpdate() {

}

void FreeCam::RenderGUI() {
	if (ImGui::CollapsingHeader("Free Camera")) {
		ImGui::Indent();
		if (
            //ImGui::Checkbox("On/Off", &enabled)
            ToggleSwitch("On/Off", &enabled)
            ) {
			// enabled state is directly managed by BaseModule
            if (enabled)
                HookManager::install(app::AzurWorld_OnUpdate, AzurWorld_OnUpdate_FreeCam_Hook);
            else {
                DisableFreeCam();
                HookManager::detach(AzurWorld_OnUpdate_FreeCam_Hook);
            }
                
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


void FreeCam::EnableFreeCam() {
    FreeCam& FreeCamera = FreeCam::GetInstance();

    freeCam = reinterpret_cast<app::GameObject*>(freeCamObj);

    freeCam_Transform = app::GameObject_get_transform(freeCam, nullptr);
    auto freeCam_Transform_position = app::Transform_get_position(freeCam_Transform, nullptr);

    freeCam_Camera = app::GameObject_GetComponentByName(freeCam, string_to_il2cppi_app("Camera"), nullptr);
    mainCam_Camera = app::GameObject_GetComponentByName(mainCam, string_to_il2cppi_app("Camera"), nullptr);

    if (!FCamisEnabled) {
        targetRotation.InitializeFromTransform(freeCam_Transform);
        currentRotation.InitializeFromTransform(freeCam_Transform);
        app::Camera_CopyFrom(RCAST(app::Camera*, freeCam_Camera),
            RCAST(app::Camera*, mainCam_Camera), nullptr);
        
        targetPosition = freeCam_Transform_position;
        FCamisEnabled = true;
    }

    app::GameObject_SetActive(mainCam, false, nullptr);
    app::GameObject_SetActive(freeCam, true, nullptr);

    if (KeyBinds::IsKeyDown(FreeCamera.f_Forward)) {
        auto forward = app::Transform_get_forward(freeCam_Transform, nullptr);
        targetPosition.x += forward.x * FreeCamera.MoveSpeed;
        targetPosition.y += forward.y * FreeCamera.MoveSpeed;
        targetPosition.z += forward.z * FreeCamera.MoveSpeed;
    }

    if (KeyBinds::IsKeyDown(FreeCamera.f_Backward)) {
        auto forward = app::Transform_get_forward(freeCam_Transform, nullptr);
        targetPosition.x -= forward.x * FreeCamera.MoveSpeed;
        targetPosition.y -= forward.y * FreeCamera.MoveSpeed;
        targetPosition.z -= forward.z * FreeCamera.MoveSpeed;
    }

    if (KeyBinds::IsKeyDown(FreeCamera.f_Left)) {
        auto right = app::Transform_get_right(freeCam_Transform, nullptr);
        targetPosition.x -= right.x * FreeCamera.MoveSpeed;
        targetPosition.y -= right.y * FreeCamera.MoveSpeed;
        targetPosition.z -= right.z * FreeCamera.MoveSpeed;
    }

    if (KeyBinds::IsKeyDown(FreeCamera.f_Right)) {
        auto right = app::Transform_get_right(freeCam_Transform, nullptr);
        targetPosition.x += right.x * FreeCamera.MoveSpeed;
        targetPosition.y += right.y * FreeCamera.MoveSpeed;
        targetPosition.z += right.z * FreeCamera.MoveSpeed;
    }

    if (KeyBinds::IsKeyDown(FreeCamera.f_Up)) {
        auto up = app::Transform_get_up(freeCam_Transform, nullptr);
        targetPosition.x += up.x * FreeCamera.MoveSpeed;
        targetPosition.y += up.y * FreeCamera.MoveSpeed;
        targetPosition.z += up.z * FreeCamera.MoveSpeed;
    }

    if (KeyBinds::IsKeyDown(FreeCamera.f_Down)) {
        auto up = app::Transform_get_up(freeCam_Transform, nullptr);
        targetPosition.x -= up.x * FreeCamera.MoveSpeed;
        targetPosition.y -= up.y * FreeCamera.MoveSpeed;
        targetPosition.z -= up.z * FreeCamera.MoveSpeed;
    }

    if (KeyBinds::IsKeyDown(FreeCamera.f_LeftRoll))
        targetRotation.roll += FreeCamera.RollSpeed;

    if (KeyBinds::IsKeyDown(FreeCamera.f_RightRoll))
        targetRotation.roll -= FreeCamera.RollSpeed;

    if (KeyBinds::IsKeyDown(FreeCamera.f_ResetRoll))
        targetRotation.roll = 0.f;

    if (KeyBinds::IsKeyDown(FreeCamera.f_IncFOV))
        smoothFOV += FreeCamera.FOVSpeed;
    if (KeyBinds::IsKeyDown(FreeCamera.f_DecFOV))
        smoothFOV -= FreeCamera.FOVSpeed;

    auto mouseX = app::Input_GetAxis(string_to_il2cppi_app("Mouse X"), nullptr);
    auto mouseY = app::Input_GetAxis(string_to_il2cppi_app("Mouse Y"), nullptr);
    auto mouseInput = app::Vector2{ mouseX, mouseY * -1.0f };
    targetRotation.yaw += mouseInput.x * FreeCamera.LookSens;
    targetRotation.pitch += mouseInput.y * FreeCamera.LookSens;

    currentRotation.UpdateTransform(freeCam_Transform);

    smoothPosition =
        app::Vector3_Lerp(freeCam_Transform_position, targetPosition, FreeCamera.MovSmoothing, nullptr);
    app::Transform_set_position(freeCam_Transform, smoothPosition, nullptr);
    smoothFOV =
        app::Mathf_Lerp(app::Camera_get_fieldOfView(reinterpret_cast<app::Camera*>(freeCam_Camera), nullptr),
            FreeCamera.FOV, FreeCamera.FovSmoothing, nullptr);
    app::Camera_set_fieldOfView(reinterpret_cast<app::Camera*>(freeCam_Camera), smoothFOV, nullptr);
    currentRotation.LerpTowards(targetRotation, FreeCamera.LookSmoothing,
        FreeCamera.RollSmoothing);
}

void FreeCam::DisableFreeCam() {
    if (freeCamObj != nullptr) {
        app::GameObject_SetActive(reinterpret_cast<app::GameObject*>(freeCamObj), false, nullptr);
    }
    if (mainCam != nullptr) {
        app::GameObject_SetActive(mainCam, true, nullptr);
    }
    FCamisEnabled = false;
}

void FreeCam::AzurWorld_OnUpdate_FreeCam_Hook(app::AzurWorld* __this, MethodInfo* method) {
    auto& FreeCamera = FreeCam::GetInstance();
    
    if (FreeCamera.enabled) {
        if (FreeCamera.mainCam == nullptr) {
            auto mainCamc = app::Camera_get_main(nullptr);
            FreeCamera.mainCam = app::Component_get_gameObject(reinterpret_cast<app::Component*>(mainCamc), nullptr);

        }
        
        if (FreeCamera.freeCamObj == nullptr && FreeCamera.mainCam) {
            auto mainCamTransform = app::GameObject_get_transform(FreeCamera.mainCam, nullptr);
            auto mainCamPos = app::Transform_get_position(mainCamTransform, nullptr);
 
            auto mainCamRot = app::Transform_get_rotation(mainCamTransform, nullptr);

            
            FreeCamera.freeCamObj = app::Object_1_Instantiate(reinterpret_cast<app::Object_1*>(FreeCamera.mainCam), mainCamPos, mainCamRot, nullptr);

            
            auto CinemachineBrain = app::GameObject_GetComponentByName(
                reinterpret_cast<app::GameObject*>(FreeCamera.freeCamObj), string_to_il2cppi_app("CinemachineBrain"), nullptr);
            
            if (CinemachineBrain != nullptr) {
                app::Object_1_DestroyImmediate_1(reinterpret_cast<app::Object_1*>(CinemachineBrain), nullptr);
            }
            
            app::GameObject_SetActive(reinterpret_cast<app::GameObject*>(FreeCamera.freeCamObj), false, nullptr);
        }
        
        if (FreeCamera.freeCamObj != nullptr) {
            FreeCamera.EnableFreeCam();
        }
    } else {
        FreeCamera.DisableFreeCam();
    }
    CALL_ORIGIN(AzurWorld_OnUpdate_FreeCam_Hook, __this,method);
}


