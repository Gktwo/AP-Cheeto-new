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
    virtual void Update() = 0;
    virtual void RenderGUI() = 0;
    virtual void RenderOverlay() = 0;
    virtual void ProcessHotkeys() = 0;

    virtual void OnGameUpdate() {}
    virtual void OnRender() {}

    virtual void LoadConfig() {}
    virtual void SaveConfig() {}

protected:
    std::string module_name;
    bool enabled;
};