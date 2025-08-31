#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/PlayTAB.h"

void PlayTAB::Render() {
    if (ImGui::BeginTabItem("Play")) {
        ImGui::Spacing();
        
        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Play Features");
        ImGui::Separator();
        ImGui::Spacing();
        
        ImGui::Text("Play-related features will be added here.");

        ImGui::EndTabItem();
    }
}

