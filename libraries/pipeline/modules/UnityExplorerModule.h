#pragma once
#include "BaseModule.h"
#include "imgui/imgui.h"
#include "pch-il2cpp.h"
#include <vector>
#include <string>
#include <chrono>

class UnityExplorerModule : public BaseModule {
public:
    // Singleton pattern
    static UnityExplorerModule& GetInstance();
    
    virtual ~UnityExplorerModule() = default;
    
    // Delete copy constructor and assignment operator
    UnityExplorerModule(const UnityExplorerModule&) = delete;
    UnityExplorerModule& operator=(const UnityExplorerModule&) = delete;
    
    // BaseModule interface implementation
    void Initialize() override;
    void Shutdown() override;
    void OnUpdate() override;
    void RenderGUI() override;
    void RenderOverlay() override;
    void ProcessHotkeys() override;
    
    // Independent window rendering
    void RenderWindow();
    
    // Module uses BaseModule's enabled variable directly
    
private:
    UnityExplorerModule();  // Private constructor for singleton
    

    bool autoRefresh;
    float refreshInterval;
    std::chrono::steady_clock::time_point lastRefreshTime;
    
    std::vector<std::string> sceneNames;
    std::vector<app::Scene> scenes;
    int selectedSceneIndex;
    
    char searchFilter[256];
    
    // Inspector related variables
    bool showInspector;
    app::GameObject* selectedGameObject;
    
    void RefreshSceneList();
    void RenderSceneSelector();
    void RenderGameObjectHierarchy(app::GameObject* obj, int index, const std::string& prefix = "");
    void RenderRefreshControls();
    void RenderInspector();
    bool ShouldShowGameObject(const std::string& objName);
};