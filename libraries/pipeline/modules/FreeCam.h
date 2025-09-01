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


    static void AzurWorld_OnUpdate_FreeCam_Hook(app::AzurWorld* __this, MethodInfo* method);



};