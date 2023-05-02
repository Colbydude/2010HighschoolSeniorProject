#pragma once

#include <windows.h>

extern bool GamePreLoad(void);
extern bool GameInit(void);
extern void GameUpdate(float);
extern void GameRender(float);
extern void GameEnd(void);