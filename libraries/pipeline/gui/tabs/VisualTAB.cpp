#include "pch-il2cpp.h"
#include "VisualTAB.h"
#include <imgui/imgui.h>
#include "../../modules/FPSModule.h"
#include "../../modules/FreeCam.h"
#include "../../modules/NoFog.h"
#include "../../modules/FpsUnlocker.h"

void VisualTAB::Render() {
    if (ImGui::BeginTabItem("Visual")) {
        // Call FPS module to render its GUI
        FPSModule::GetInstance().RenderGUI();
        FreeCam::GetInstance().RenderGUI();
        NoFog::GetInstance().RenderGUI();
		FpsUnlocker::GetInstance().RenderGUI();
        ImGui::EndTabItem();
    }
}

