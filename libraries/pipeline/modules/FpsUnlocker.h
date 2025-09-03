#pragma once
#include "BaseModule.h"
#include "imgui/imgui.h"

class FpsUnlocker : public BaseModule {
public:
    // Singleton pattern
    static FpsUnlocker& GetInstance() {
        static FpsUnlocker instance;
        return instance;
    }

    virtual ~FpsUnlocker() = default;

    // Delete copy constructor and assignment operator
    FpsUnlocker(const FpsUnlocker&) = delete;
    FpsUnlocker& operator=(const FpsUnlocker&) = delete;

    // BaseModule interface implementation
    void Initialize() override;
    void Shutdown() override;
    void OnUpdate() override;
    void RenderGUI() override;
    void RenderOverlay() override;
    void ProcessHotkeys() override;



    // Module uses BaseModule's enabled variable directly

private:
    FpsUnlocker();  // Private constructor for singleton
    bool Unlimited;
    int32_t fpsvalue;

    static  void AzurWorld_OnUpdate_fpsunlocker_Hook(app::AzurWorld* __this, MethodInfo* method);

    void EnableFpsUnlocker();
    void DisableFpsUnlocker();

};