#pragma once
#include "BaseModule.h"
#include "imgui/imgui.h"

class PlayerProfile : public BaseModule {
public:
    // Singleton pattern
    static PlayerProfile& GetInstance() {
        static PlayerProfile instance;
        return instance;
    }

    virtual ~PlayerProfile() = default;

    // Delete copy constructor and assignment operator
    PlayerProfile(const PlayerProfile&) = delete;
    PlayerProfile& operator=(const PlayerProfile&) = delete;

    // BaseModule interface implementation
    void Initialize() override;
    void Shutdown() override;
    void OnUpdate() override;
    void RenderGUI() override;
    void RenderOverlay() override;
    void ProcessHotkeys() override;



    // Module uses BaseModule's enabled variable directly

private:
    std::string  uidtext;
    PlayerProfile();  // Private constructor for singleton


};