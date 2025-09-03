#include "pch-il2cpp.h"
#include "UnityExplorerModule.h"
#include "../settings.h"
#include "ModuleRegistry.h"
#include <algorithm>
#include <cctype>


// Constructor
UnityExplorerModule::UnityExplorerModule() : BaseModule("Unity Explorer") {
	enabled = false;

	autoRefresh = false;
	refreshInterval = 3.0f;
	selectedSceneIndex = 0;
	lastRefreshTime = std::chrono::steady_clock::now();
	memset(searchFilter, 0, sizeof(searchFilter));
}


UnityExplorerModule& UnityExplorerModule::GetInstance() {
	static UnityExplorerModule instance;
	return instance;
}

void UnityExplorerModule::Initialize()
{

	sceneNames.clear();
	scenes.clear();
	// RefreshSceneList will only be called when auto refresh is enabled or manually triggered
}

void UnityExplorerModule::OnUpdate()
{
	if (!enabled) return;

	if (autoRefresh) {
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastRefreshTime).count();

		if (elapsed >= refreshInterval * 1000.0f) {
			RefreshSceneList();
			lastRefreshTime = currentTime;
		}
	}
}

void UnityExplorerModule::RenderGUI()
{
	// Unity Explorer window toggle

	ToggleSwitch("Unity Explorer Window", &enabled);

}

void UnityExplorerModule::RenderWindow()
{
	if (!enabled) return;


	if (ImGui::Begin("Unity Explorer", &enabled, ImGuiWindowFlags_None)) {
		RenderSceneSelector();
		ImGui::Separator();
		RenderRefreshControls();
		ImGui::Separator();
		
		// Search filter
		ImGui::Text("Search Filter:");
		ImGui::SetNextItemWidth(300);
		ImGui::InputText("##SearchFilter", searchFilter, sizeof(searchFilter));
		ImGui::Separator();

		// Only render scene hierarchy if scenes have been loaded
		if (scenes.empty()) {
			ImGui::Text("No scenes loaded. Click 'Refresh' or enable 'Auto Refresh' to load scenes.");
		}
		else if (selectedSceneIndex >= 0 && selectedSceneIndex < scenes.size()) {
			app::Scene& selectedScene = scenes[selectedSceneIndex];
			std::string sceneName = sceneNames[selectedSceneIndex];

			if (ImGui::CollapsingHeader(("Scene: " + sceneName).c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
				ImGui::Indent();
				app::GameObject__Array* objs = app::Scene_GetRootGameObjects(&selectedScene, nullptr);
				if (objs && objs->max_length > 0) {
					for (int i = 0; i < objs->max_length; i++) {
						app::GameObject* obj = objs->vector[i];
						if (obj) {
							RenderGameObjectHierarchy(obj, i);
						}
					}
				}
				else {
					ImGui::Text("No GameObjects found in this scene.");
				}
				ImGui::Unindent();
			}
		}
	}
	ImGui::End();

}

void UnityExplorerModule::RenderOverlay()
{

	RenderWindow();
}

void UnityExplorerModule::ProcessHotkeys()
{
	// No hotkeys for Unity Explorer currently
}

void UnityExplorerModule::RefreshSceneList()
{
	sceneNames.clear();
	scenes.clear();

	app::Scene__Array* sceneArray = app::SceneManager_GetAllScenes(nullptr);
	if (sceneArray && sceneArray->max_length > 0) {
		for (int i = 0; i < sceneArray->max_length; i++) {
			app::Scene scene = sceneArray->vector[i];
			std::string sceneName = il2cppi_to_string(app::Scene_get_name(&scene, nullptr));

			sceneNames.push_back(sceneName);
			scenes.push_back(scene);
		}
	}

	// Ensure selected index is valid
	if (selectedSceneIndex >= scenes.size()) {
		selectedSceneIndex = scenes.empty() ? -1 : 0;
	}
}

void UnityExplorerModule::RenderRefreshControls()
{
	// Manual refresh button
	if (ImGui::Button("Refresh")) {
		RefreshSceneList();
	}

	ImGui::SameLine();

	// Auto refresh toggle
	if (ToggleSwitch("Auto Refresh", &autoRefresh)) {
		if (autoRefresh) {
			lastRefreshTime = std::chrono::steady_clock::now();
		}
	}

	// Refresh interval slider
	if (autoRefresh) {
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::SliderFloat("Interval (s)", &refreshInterval, 0.1f, 10.0f, "%.1f");
	}

	ImGui::Text("Scenes found: %d", (int)scenes.size());
}

void UnityExplorerModule::RenderSceneSelector()
{
	if (scenes.empty()) {
		ImGui::Text("No scenes available. Click 'Refresh Scenes' to load.");
		return;
	}

	// Scene dropdown
	ImGui::Text("Select Scene:");
	ImGui::SetNextItemWidth(300);

	if (ImGui::BeginCombo("##SceneCombo", selectedSceneIndex >= 0 ? sceneNames[selectedSceneIndex].c_str() : "Select Scene")) {
		for (int i = 0; i < sceneNames.size(); i++) {
			bool isSelected = (selectedSceneIndex == i);
			if (ImGui::Selectable(sceneNames[i].c_str(), isSelected)) {
				if (selectedSceneIndex != i) {
					selectedSceneIndex = i;
					// Auto refresh when scene changes
					RefreshSceneList();
				}
			}
			if (isSelected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
}

void UnityExplorerModule::RenderGameObjectHierarchy(app::GameObject* obj, int index, const std::string& prefix)
{
	if (!obj) return;

	std::string objName = il2cppi_to_string(app::Object_1_GetName(RCAST(app::Object_1*, obj), nullptr));
	app::Transform* trans = app::GameObject_get_transform(obj, nullptr);

	if (!trans) {
		if (ShouldShowGameObject(objName)) {
			ImGui::Text("%s [%d]: %s (No Transform)", prefix.c_str(), index, objName.c_str());
		}
		return;
	}

	int childCount = app::Transform_get_childCount(trans, nullptr);
	
	// Check if this object or any of its children should be shown
	bool shouldShowThis = ShouldShowGameObject(objName);
	bool hasVisibleChildren = false;
	
	// Check if any children match the filter
	if (!shouldShowThis && childCount > 0) {
		for (int i = 0; i < childCount; i++) {
			app::Transform* child = app::Transform_GetChild(trans, i, nullptr);
			if (child) {
				app::GameObject* childObj = app::Component_get_gameObject(RCAST(app::Component*, child), nullptr);
				if (childObj) {
					std::string childName = il2cppi_to_string(app::Object_1_GetName(RCAST(app::Object_1*, childObj), nullptr));
					if (ShouldShowGameObject(childName)) {
						hasVisibleChildren = true;
						break;
					}
				}
			}
		}
	}

	// Show this object if it matches filter or has visible children
	if (shouldShowThis || hasVisibleChildren) {
		if (childCount > 0) {
			std::string nodeLabel = prefix + " [" + std::to_string(index) + "]: " + objName;
			if (ImGui::TreeNode(nodeLabel.c_str())) {
				for (int i = 0; i < childCount; i++) {
					app::Transform* child = app::Transform_GetChild(trans, i, nullptr);
					if (child) {
						app::GameObject* childObj = app::Component_get_gameObject(RCAST(app::Component*, child), nullptr);
						if (childObj) {
							RenderGameObjectHierarchy(childObj, i, "  ");
						}
					}
				}
				ImGui::TreePop();
			}
		}
		else {
			ImGui::Text("%s [%d]: %s", prefix.c_str(), index, objName.c_str());
		}
	}
}

bool UnityExplorerModule::ShouldShowGameObject(const std::string& objName)
{
	// If search filter is empty, show all objects
	if (strlen(searchFilter) == 0) {
		return true;
	}
	
	// Convert both strings to lowercase for case-insensitive search
	std::string lowerObjName = objName;
	std::string lowerFilter = searchFilter;
	
	std::transform(lowerObjName.begin(), lowerObjName.end(), lowerObjName.begin(), ::tolower);
	std::transform(lowerFilter.begin(), lowerFilter.end(), lowerFilter.begin(), ::tolower);
	
	// Check if object name contains the search filter
	return lowerObjName.find(lowerFilter) != std::string::npos;
}

void UnityExplorerModule::Shutdown()
{
	enabled = false;
	sceneNames.clear();
	scenes.clear();
	selectedSceneIndex = 0;
}