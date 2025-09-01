#pragma once
#include "BaseModule.h"
#include "imgui/imgui.h"

class FPSModule : public BaseModule {
public:
    // Singleton pattern
    static FPSModule& GetInstance() {
        static FPSModule instance;
        return instance;
    }
    
    virtual ~FPSModule() = default;
    
    // Delete copy constructor and assignment operator
    FPSModule(const FPSModule&) = delete;
    FPSModule& operator=(const FPSModule&) = delete;

    // BaseModule interface implementation
    void Initialize() override;
    void Shutdown() override;
    void OnUpdate() override;
    void RenderGUI() override;
    void RenderOverlay() override;
    void ProcessHotkeys() override;
    


    // Module uses BaseModule's enabled variable directly

private:
    FPSModule();  // Private constructor for singleton
    
    uint8_t toggle_key;
    
    // Helper functions
    ImVec4 GetFPSColor(float fps) const;
    ImVec4 GetFrameTimeColor(float frame_time) const;
};