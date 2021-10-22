#pragma once

#define WindowName "Змейка"
#define WindowSizeX  801 //676 ?
#define WindowSizeY 629 //401 ? 381

#define INIT(a) static bool init = false; if (!init) { init = true; a; }
