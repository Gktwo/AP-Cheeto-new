#include "pch-il2cpp.h"

#include <Windows.h>
#include "detours/detours.h"
#include "InitHooks.h"
#include <iostream>
#include "DirectX.h"
#include "pipeline/settings.h"
#include <helpers.h>

bool HookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (const auto error = DetourAttach(ppPointer, pDetour); error != NO_ERROR) {
		std::cout << "[ERROR]: Failed to hook " << functionName << ", error " << error << std::endl;
		return false;
	}
	std::cout << "[HOOKED]: " << functionName << std::endl;
	return true;
}

#define HOOKFUNC(n) if (!HookFunction(&(PVOID&)n, d##n, #n)) return;

bool UnhookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (const auto error = DetourDetach(ppPointer, pDetour); error != NO_ERROR) {
		std::cout << "[ERROR]: Failed to unhook " << functionName << ", error " << error << std::endl;
		return false;
	}
	std::cout << "[UNHOOKED]: " << functionName << std::endl;
	return true;
}

#define UNHOOKFUNC(n) if (!UnhookFunction(&(PVOID&)n, d##n, #n)) return;

void DetourInitilization() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	dx11api d3d11 = dx11api();
	if (!d3d11.presentFunction) {
		std::cout << "[ERROR]: Unable to retrieve IDXGISwapChain::Present method" << std::endl;
		return;
	}

	oPresent = d3d11.presentFunction;
	if (!oPresent) {
		std::cout << "[ERROR]: oPresent is null!" << std::endl;
		return;
	}

	std::cout << "[INFO]: Attempting to hook oPresent at address: " << oPresent << std::endl;

	if (!HookFunction(&(PVOID&)oPresent, dPresent, "D3D_PRESENT_FUNCTION")) {
		DetourTransactionAbort();
		return;
	}

	DetourTransactionCommit();
}

void DetourUninitialization() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	if (DetourDetach(&(PVOID&)oPresent, dPresent) != 0) return;

	if (DetourTransactionCommit() == NO_ERROR) {
		DirectX::Shutdown();
	}
}


