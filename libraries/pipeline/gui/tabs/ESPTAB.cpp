#include "pch-il2cpp.h"
#include "pipeline/gui/tabs/ESPTAB.h"
#include "../../modules/ESPModule.h"

void ESPTAB::Render() {
	if (ImGui::BeginTabItem("ESP")) {
		// Call ESP module to render its GUI
		ESPModule::GetInstance().RenderGUI();

		ImGui::EndTabItem();
	}
}