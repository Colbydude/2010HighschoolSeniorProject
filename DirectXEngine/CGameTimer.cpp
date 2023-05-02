#include "CGameTimer.h"

namespace DirectXEngine
{
	CGameTimer::CGameTimer(void)
	{
		this->_start = timeGetTime();
	}

	DWORD CGameTimer::GetTime(void)
	{
		return timeGetTime();
	}

	DWORD CGameTimer::GetStartTime(void)
	{
		return this->_start;
	}

	DWORD CGameTimer::GetRunTime(void)
	{
		return (this->GetTime() - this->GetStartTime());
	}

	void CGameTimer::Reset(void)
	{
		this->_start = this->GetTime();
	}
};