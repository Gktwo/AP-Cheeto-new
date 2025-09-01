#pragma once
#include <string>

class BaseModule {
public:
    BaseModule(const std::string& name) : module_name(name), enabled(false) {}
    virtual ~BaseModule() = default;

    const std::string& GetName() const { return module_name; }
    bool IsEnabled() const { return enabled; }
    void SetEnabled(bool state) { enabled = state; }

    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual void Update() { OnUpdate(); }
    virtual void OnUpdate() {}
    virtual void RenderGUI() = 0;
    virtual void RenderOverlay() = 0;
    virtual void ProcessHotkeys() = 0;

    virtual void LoadConfig() {}
    virtual void SaveConfig() {}

protected:
    virtual void OnGameUpdate() {}
    virtual void OnRender() {}

    std::string module_name;
    bool enabled;
};

// Modules can directly use the enabled member variable from BaseModule
// No macros needed - just set enabled = true/false as needed

