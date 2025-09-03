#pragma once
#include "BaseModule.h"
#include "imgui/imgui.h"
#include "pch-il2cpp.h"

// Entity display info structure
struct EntityDisplayInfo {
    bool shouldShow;
    ImColor color;
};

class ESPModule : public BaseModule {
public:
    // Singleton pattern
    static ESPModule& GetInstance() {
        static ESPModule instance;
        return instance;
    }
    
    virtual ~ESPModule() = default;
    
    // Delete copy constructor and assignment operator
    ESPModule(const ESPModule&) = delete;
    ESPModule& operator=(const ESPModule&) = delete;

    // BaseModule interface implementation
    void Initialize() override;
    void Shutdown() override;
    void OnUpdate() override;
    void RenderGUI() override;
    void RenderOverlay() override;
    void ProcessHotkeys() override;
    


    // Module uses BaseModule's enabled variable directly

private:
    ESPModule();  // Private constructor for singleton
    
    uint8_t toggle_key;
    
    // Display type control variables
    bool show_monster;
    bool show_npc;
    bool show_friendly;
    bool show_puzzle;
    bool show_all;
    
    // Display info control variables
    bool show_distance;
    bool show_configid;
    bool show_configname;
    bool show_entityid;
    bool show_type;
    
    // Color definitions
    ImColor red, orange, yellow, green, blue, qing, purple, white, deeppink, pink, black, gray;
    
    // Helper functions
    void drawESP();
    std::string addtext(std::string& text, const std::string& newtext, bool first = false);
    EntityDisplayInfo getEntityDisplayInfo(app::EEntityType__Enum type) const;
};