#pragma once
#include "BaseModule.h"
#include "imgui/imgui.h"

class NoFog : public BaseModule {
public:
    // Singleton pattern
    static NoFog& GetInstance() {
        static NoFog instance;
        return instance;
    }

    virtual ~NoFog() = default;

    // Delete copy constructor and assignment operator
    NoFog(const NoFog&) = delete;
    NoFog& operator=(const NoFog&) = delete;

    // BaseModule interface implementation
    void Initialize() override;
    void Shutdown() override;
    void OnUpdate() override;
    void RenderGUI() override;
    void RenderOverlay() override;
    void ProcessHotkeys() override;



    // Module uses BaseModule's enabled variable directly

private:
    NoFog();  // Private constructor for singleton


    // Hook function
    static void AzurWorld_OnUpdate_no_fog_Hook(app::AzurWorld* __this, MethodInfo* method);

    // Helper functions
    void EnableNoFog();
    void DisableNoFog();
    
};