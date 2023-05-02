#pragma once

// Trim the size of Windows.h.
#define WIN32_LEAN_AND_MEAN

// Global Header Files.
#include <Windows.h>

// Function Declarations.
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);