#pragma once

#define DRAW_WAY_DIRECTX	1
#define DRAW_WAY_OPENGL		2

#define USE_DIRECTX9	0x00000001
#define USE_DIRECTX10	0x00000002
#define USE_DIRECTX11	0x00000003

#include <time.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include <d3dx9tex.h>

extern IDirect3DDevice9* g_pDevice;
extern HWND g_hWnd;

static const int winWidth = 640;
static const int winHigh = 480;