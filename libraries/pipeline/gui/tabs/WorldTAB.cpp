#include "pch-il2cpp.h"
#include "WorldTAB.h"
#include <imgui/imgui.h>
#include "pipeline/HookManager.h"
#include <iostream>

void WorldTAB::Render() {
    if (ImGui::BeginTabItem("World")) {
        ImGui::Spacing();
        
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.5f, 1.0f), "World Features");
        ImGui::Separator();
        ImGui::Spacing();
        
        // 空的UI界面
        ImGui::Text("World功能开发中...");
        ImGui::Text("这里将包含世界信息、实体列表、传送等功能");
        
        ImGui::EndTabItem();
    }
}

