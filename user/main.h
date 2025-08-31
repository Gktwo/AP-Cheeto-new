#pragma once
#include <windows.h>

extern HMODULE hModule;
extern HANDLE hUnloadEvent;

void Run(LPVOID lpParam);
