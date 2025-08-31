#include "pch-il2cpp.h"

#include "DirectX.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "imgui/imstb_truetype.h"
#include "pipeline/gui/Menu.h"
#include <mutex>
#include "pipeline/Settings.h"
#include <future>
#include "pipeline/keybinds.h"
#include <iostream>
#include <pipeline/gui/GUITheme.h>
#include "pipeline/HYWenHei.hpp"
#include "pipeline/gui/tabs/SettingsTAB.h"
#include "pipeline/gui/tabs/ESPTAB.h"
#include "pipeline/modules/ModuleManager.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND DirectX::window;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* pRenderTargetView = NULL;
D3D_PRESENT_FUNCTION oPresent = nullptr;
WNDPROC oWndProc;

HANDLE DirectX::hRenderSemaphore;
constexpr DWORD MAX_RENDER_THREAD_COUNT = 5;

typedef struct Cache
{
	ImGuiWindow* Window = nullptr;
	ImVec2       Winsize;
} cache_t;

static cache_t s_Cache;

ImVec2 DirectX::GetWindowSize()
{
	if (app::Screen_get_fullScreen(nullptr))
	{
		RECT rect;
		GetWindowRect(window, &rect);

		return { (float)(rect.right - rect.left),  (float)(rect.bottom - rect.top) };
	}

	return { (float)app::Screen_get_width(nullptr), (float)app::Screen_get_height(nullptr) };

}

LRESULT __stdcall dWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (!settings.ImGuiInitialized)
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);

	if (uMsg == WM_SIZE) {
		WaitForSingleObject(DirectX::hRenderSemaphore, INFINITE);
		if (pRenderTargetView) {
			pRenderTargetView->Release();
			pRenderTargetView = nullptr;
		}
		ReleaseSemaphore(DirectX::hRenderSemaphore, 1, NULL);
	}

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	KeyBinds::WndProc(uMsg, wParam, lParam);

	if (KeyBinds::IsKeyPressed(settings.KeyBinds.Toggle_Menu))
	{
		settings.bShowMenu = !settings.bShowMenu;
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool ImGuiInitialization(IDXGISwapChain* pSwapChain) {
	if ((pDevice != NULL) || (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))) {
		pDevice->GetImmediateContext(&pContext);
		DXGI_SWAP_CHAIN_DESC sd;
		pSwapChain->GetDesc(&sd);
		DirectX::window = sd.OutputWindow;
		ID3D11Texture2D* pBackBuffer = NULL;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if (!pBackBuffer)
			return false;
		pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
		pBackBuffer->Release();
		oWndProc = (WNDPROC)SetWindowLongPtr(DirectX::window, GWLP_WNDPROC, (LONG_PTR)dWndProc);


		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImFontConfig fontConfig;
		fontConfig.FontDataOwnedByAtlas = false;
		io.FontDefault = io.Fonts->AddFontFromMemoryCompressedTTF(
			HYWenHei_compressed_data, *HYWenHei_compressed_data,
			15.0f, &fontConfig, io.Fonts->GetGlyphRangesChineseFull());
		ImGui_ImplWin32_Init(DirectX::window);
		ImGui_ImplDX11_Init(pDevice, pContext);
		
		DirectX::hRenderSemaphore = CreateSemaphore(
			NULL,
			MAX_RENDER_THREAD_COUNT,
			MAX_RENDER_THREAD_COUNT,
			NULL);
		return true;
	}

	return false;
}

std::once_flag init_d3d;
HRESULT __stdcall dPresent(IDXGISwapChain* __this, UINT SyncInterval, UINT Flags) {
	std::call_once(init_d3d, [&] {
		if (SUCCEEDED(__this->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
		}
		});
	if (!settings.ImGuiInitialized) {
		if (ImGuiInitialization(__this)) {
			ImVec2 size = DirectX::GetWindowSize();
			settings.ImGuiInitialized = true;
			std::cout << "[INFO]: ImGui Initialized successfully!\n";
			std::cout << "[INFO]: Fullscreen: " << app::Screen_get_fullScreen(nullptr) << std::endl;
			std::cout << "[INFO]: DirectX Window Size: " << +size.x << "x" << +size.y << std::endl;
			
			// Initialize module manager
			MODULE_MANAGER.InitializeAll();
		}
		else {
			ReleaseSemaphore(DirectX::hRenderSemaphore, 1, NULL);
			return oPresent(__this, SyncInterval, Flags);
		}
	}

	WaitForSingleObject(DirectX::hRenderSemaphore, INFINITE);

	// resolution changed
	if (!pRenderTargetView) {
		ID3D11Texture2D* pBackBuffer = nullptr;
		__this->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		assert(pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
		pBackBuffer->Release();

		ImVec2 size = DirectX::GetWindowSize();
		std::cout << "[INFO]: DirectX Window Size: " << +size.x << "x" << +size.y << std::endl;
	}

	il2cpp_gc_disable();

	ApplyTheme();
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Process hotkeys for all modules
	MODULE_MANAGER.ProcessAllHotkeys();
	
	// Update all modules
	MODULE_MANAGER.UpdateAll();
	
	if (settings.bShowMenu)
	{
		Menu::Render();
	}

	// Render all module overlays (ESP, FPS, etc.)
	MODULE_MANAGER.RenderAllOverlays();

	ImGui::EndFrame();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	il2cpp_gc_enable();

	HRESULT result = oPresent(__this, SyncInterval, Flags);

	ReleaseSemaphore(DirectX::hRenderSemaphore, 1, NULL);

	return result;
}

void DirectX::Shutdown() {
	assert(hRenderSemaphore != NULL);
	for (uint8_t i = 0; i < MAX_RENDER_THREAD_COUNT; i++)
	{
		assert(WaitForSingleObject(hRenderSemaphore, INFINITE) == WAIT_OBJECT_0);
	}
	
	// Shutdown module manager
	MODULE_MANAGER.ShutdownAll();
	
	oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	CloseHandle(hRenderSemaphore);
}