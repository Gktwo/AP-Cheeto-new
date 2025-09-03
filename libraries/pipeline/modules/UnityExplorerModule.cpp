#include "pch-il2cpp.h"
#include "UnityExplorerModule.h"
#include "../settings.h"
#include "ModuleRegistry.h"


// Constructor
UnityExplorerModule::UnityExplorerModule() : BaseModule("Unity Explorer") {
	enabled = false;

	autoRefresh = false;
	refreshInterval = 3.0f;
	selectedSceneIndex = 0;
	lastRefreshTime = std::chrono::steady_clock::now();
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
	// Unity Explorer doesn't need overlay rendering
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
		ImGui::Text("%s [%d]: %s (No Transform)", prefix.c_str(), index, objName.c_str());
		return;
	}

	int childCount = app::Transform_get_childCount(trans, nullptr);

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

void UnityExplorerModule::Shutdown()
{
	enabled = false;
	sceneNames.clear();
	scenes.clear();
	selectedSceneIndex = 0;
}