#pragma once
#include "imgui/imgui.h"
#include "../keybinds.h"
#include <string>

class BaseModule {
public:
    BaseModule(const std::string& name) : module_name(name), enabled(false) {}
    virtual ~BaseModule() = default;

    // Module identification
    const std::string& GetName() const { return module_name; }
    bool IsEnabled() const { return enabled; }
    void SetEnabled(bool state) { enabled = state; }

    // Core module functions - must be implemented by derived classes
    virtual void Initialize() = 0;          // Initialize module resources
    virtual void Shutdown() = 0;            // Cleanup module resources
    virtual void Update() = 0;              // Update module logic (called every frame)
    virtual void RenderGUI() = 0;           // Render module GUI in settings panel
    virtual void RenderOverlay() = 0;       // Render module overlay (independent drawing)
    virtual void ProcessHotkeys() = 0;      // Handle module-specific hotkeys
    
    // Optional hook functions
    virtual void OnGameUpdate() {}          // Called when game update hook is triggered
    virtual void OnRender() {}              // Called during render hook
    
    // Configuration
    virtual void LoadConfig() {}            // Load module configuration
    virtual void SaveConfig() {}            // Save module configuration

protected:
    std::string module_name;
    bool enabled;
};