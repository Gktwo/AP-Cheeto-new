#pragma once
#include "BaseModule.h"
#include "imgui/imgui.h"

class WorldSpeedModule : public BaseModule {
public:
    // Singleton pattern
    static WorldSpeedModule& GetInstance() {
        static WorldSpeedModule instance;
        return instance;
    }
    
    virtual ~WorldSpeedModule() = default;
    
    // Delete copy constructor and assignment operator
    WorldSpeedModule(const WorldSpeedModule&) = delete;
    WorldSpeedModule& operator=(const WorldSpeedModule&) = delete;

    // BaseModule interface implementation
    void Initialize() override;
    void Shutdown() override;
    void OnUpdate() override;
    void RenderGUI() override;
    void RenderOverlay() override;
    void ProcessHotkeys() override;
    


    // Module uses BaseModule's enabled variable directly

private:
    WorldSpeedModule();  // Private constructor for singleton
    
    float world_speed_value;
    uint8_t toggle_key;
    
    // Hook function
    static void AzurWorld_OnUpdate_world_speed_Hook(app::AzurWorld* __this, MethodInfo* method);
    
    // Helper functions
    void EnableWorldSpeed();
    void DisableWorldSpeed();
    void ResetSpeed();
};