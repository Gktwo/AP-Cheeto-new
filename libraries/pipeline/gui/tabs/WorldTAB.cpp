#include "pch-il2cpp.h"
#include "WorldTAB.h"
#include <imgui/imgui.h>
#include "../../modules/WorldSpeedModule.h"


void WorldTAB::Render() {
    if (ImGui::BeginTabItem("World")) {
        // Call WorldSpeed module to render its GUI
        WorldSpeedModule::GetInstance().RenderGUI();
        
        ImGui::EndTabItem();
    }
}

