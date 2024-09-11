#pragma once

#define ENABLE_MUSIC 0

#ifndef APP_FULL_SIZE
#if defined(_WIN32)
#define APP_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define APP_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#else
#define APP_WIDTH 1080
#define APP_HEIGHT 840
#endif
#else
#define APP_WIDTH 1080
#define APP_HEIGHT	840
#endif

#define APP_TITLE "Plane Game"
