#pragma once

#define ENABLE_MUSIC 0
#define ENABLE_ICON 1

#define ROOT_SHADER_PATH ./Resources/Shaders/
#define ROOT_TEXTURE_PATH ./Resources/Textures/
#define CONCAT_IMPL(lhs, rhs) lhs##rhs
#define CONCAT(lhs, rhs) CONCAT_IMPL(lhs,rhs)
#define SHADERS_PATH_IMPL(__shader_name) CONCAT(ROOT_SHADER_PATH, __shader_name)
#define TEXTURE_PATH_IMPL(__texture_name) CONCAT(ROOT_TEXTURE_PATH, __texture_name)
#define AS_STR_IMPL(data) #data
#define AS_STR(data) AS_STR_IMPL(data)
#define ROOT_SHADER_PATH_STR AS_STR(ROOT_SHADER_PATH)
#define ROOT_TEXTURE_PATH_AS_STR AS_STR(ROOT_TEXTURE_PATH)
#define SHADERS_PATH(__shader_name) AS_STR(SHADERS_PATH_IMPL(__shader_name))
#define TEXTURE_PATH(__texture_name) AS_STR(TEXTURE_PATH_IMPL(__texture_name))

#define APP_FULL_SIZE

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

#if !defined(NDEBUG)
#define ENABLE_LOG
#endif

#if defined(ENABLE_LOG)
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define APP_LOG(str) OutputDebugStringA(str)
#else
#include <assert.h>
#include <iostream>
#define APP_LOG(str) std::cout << str
#endif
#else
#define APP_LOG(str) (void)str;
#endif


#if defined(USING_WINAPI)
#if defined(_WIN32) && !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#endif
