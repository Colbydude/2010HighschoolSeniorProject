#pragma once

// Global Headers.
#include <time.h>
#include <Windows.h>

namespace DirectXEngine
{
	class CGameTimer
	{
	private:
		// Marks the starting point of the timer.
		DWORD _start;
	
	public:
		// Constructor & Destructor.
		CGameTimer(void);

		// Function Declarations.
		DWORD GetTime(void);		// Retrieve the current time (in milliseconds).
		DWORD GetStartTime(void);	// Get the Timer's start time (in milliseconds).
		DWORD GetRunTime(void);		// Get the Timer's running time (in millseconds).
		void Reset(void);			// Reset the timer.
	};
};