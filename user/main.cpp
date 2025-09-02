// Generated C++ file by Il2CppInspectorPro - https://github.com/jadis0x
// Custom injected code entry point

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "il2cpp-appdata.h"
#include "helpers.h"
#include "main.h"
#include <il2cpp-init.h>

#include <pipeline/hooks/InitHooks.h>



using namespace app;

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"Logs.txt";

HMODULE hModule;
HANDLE hUnloadEvent;

DWORD WINAPI UnloadWatcherThread(LPVOID lpParam)
{
 HANDLE hEvent = static_cast<HANDLE>(lpParam);

 if (WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
 {
  std::cout << "[WARNING] Unload signal received.." << std::endl;
  DetourUninitialization();
  fclose(stdout);
  FreeConsole();
  CloseHandle(hUnloadEvent);
  FreeLibraryAndExitThread(hModule, 0);
 }
 return 0;
}

void AntiCheatManager_Initialize_hook(MethodInfo* method)
{
	std::cout << "[INFO]  AntiCheat Bypassed" << std::endl;
	return;
}
// Custom injected code entry point
void Run(LPVOID lpParam)
{
 hModule = (HMODULE)lpParam;

 // If you would like to write to a log file, specify the name above and use il2cppi_log_write()
 // il2cppi_log_write("Startup");

 // If you would like to output to a new console window, use il2cppi_new_console() to open one and redirect stdout
 //il2cppi_new_console();
 Logger_::attach().showFileName().showLineNumber().consoleOnly().enableColors();
 SetConsoleTitleA("il2cpp Game Console");

 init_il2cpp();
 HookManager::install(app::AntiCheatManager_Initialize, AntiCheatManager_Initialize_hook);
 LOG_INFO("Initializing..");
// std::cout << "[INFO] Initializing.. " << std::endl;

 // Initialize thread data - DO NOT REMOVE
 Il2CppDomain* _domain = il2cpp_domain_get();
 Il2CppThread* _thread = nullptr;

 // Check if IL2CPP domain is found
 if (_domain) {
  LOG_INFO("IL2CPP Domain Found: ");
  //std::cout << "[INFO] IL2CPP Domain Found: " << _domain << std::endl;
  
  // Attach thread to IL2CPP domain
  _thread = il2cpp_thread_attach(_domain);

  if (_thread) {
	  LOG_INFO("IL2CPP Thread Attached Successfully: ");
  // std::cout << "[INFO] IL2CPP Thread Attached Successfully: " << _thread << std::endl;
  }
  else {
	  LOG_ERROR("Failed to Attach IL2CPP Thread!");
 //  std::cout << "[ERROR] Failed to Attach IL2CPP Thread!" << std::endl;
  }
 }
 else {
	 LOG_ERROR("IL2CPP Domain Not Found!");
 // std::cout << "[ERROR] IL2CPP Domain Not Found!" << std::endl;
 }

 DetourInitilization();

 // 初始化功能页面的动态Hook
// std::cout << "[INFO] Initializing feature hooks..." << std::endl;
 //PlayTAB::InitializePlayHooks();
 //WorldTAB::InitializeWorldHooks();
// std::cout << "[INFO] Feature hooks initialized successfully." << std::endl;

 hUnloadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
 if (hUnloadEvent == NULL) {
  std::cout << "Failed to create unload event! Error code: " << GetLastError() << std::endl;
  return;
 }


 DWORD dwThreadId;
 HANDLE hWatcherThread = CreateThread(NULL, 0, UnloadWatcherThread, hUnloadEvent, 0, &dwThreadId);
 if (hWatcherThread != NULL)
 {
  CloseHandle(hWatcherThread);
 }
 else
 {
  std::cout << "[ERROR] Unable to create unload monitor thread! Error code: " << GetLastError() << std::endl;
 }
}

