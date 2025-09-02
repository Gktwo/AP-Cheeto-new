#pragma once
#include "BaseModule.h"
#include "imgui/imgui.h"

class FreeCam : public BaseModule {
public:
    // Singleton pattern
    static FreeCam& GetInstance() {
        static FreeCam instance;
        return instance;
    }

    virtual ~FreeCam() = default;

    // Delete copy constructor and assignment operator
    FreeCam(const FreeCam&) = delete;
    FreeCam& operator=(const FreeCam&) = delete;

    // BaseModule interface implementation
    void Initialize() override;
    void Shutdown() override;
    void OnUpdate() override;
    void RenderGUI() override;
    void RenderOverlay() override;
    void ProcessHotkeys() override;



    // Module uses BaseModule's enabled variable directly

private:
    FreeCam();  // Private constructor for singleton

	float MoveSpeed;
	float LookSens;
    float RollSpeed;
    float FOVSpeed;
    float FOV;
    float MovSmoothing;
    float LookSmoothing;
    float RollSmoothing;
    float FovSmoothing;

    //uint8_t toggle_key;
    uint8_t f_Forward;
    uint8_t f_Backward;
    uint8_t f_Left;
    uint8_t f_Right;
    uint8_t f_Up;
    uint8_t f_Down;
    uint8_t f_IncFOV;
    uint8_t f_DecFOV;
    uint8_t f_LeftRoll;
    uint8_t f_RightRoll;
    uint8_t f_ResetRoll;

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

    void EnableFreeCam();
    void DisableFreeCam();
    static void AzurWorld_OnUpdate_FreeCam_Hook(app::AzurWorld* __this, MethodInfo* method);


    class CameraRotation {
    public:
        float pitch, yaw, roll;

        void InitializeFromTransform(app::Transform* t) {
            auto t_eulerAngles = app::Transform_get_eulerAngles(t, nullptr);
            pitch = t_eulerAngles.x;
            yaw = t_eulerAngles.y;
            roll = t_eulerAngles.z;
        }

        void LerpTowards(CameraRotation target, float lookRotationLerpPct, float rollRotationLerpPct) {
            yaw = app::Mathf_Lerp(yaw, target.yaw, lookRotationLerpPct, nullptr);
            pitch = app::Mathf_Lerp(pitch, target.pitch, lookRotationLerpPct, nullptr);
            roll = app::Mathf_Lerp(roll, target.roll, rollRotationLerpPct, nullptr);
        }

        void UpdateTransform(app::Transform* t) {
            app::Transform_set_eulerAngles(t, app::Vector3{ pitch, yaw, roll }, nullptr);
        }
    };
    CameraRotation targetRotation = CameraRotation();
    CameraRotation currentRotation = CameraRotation();


};