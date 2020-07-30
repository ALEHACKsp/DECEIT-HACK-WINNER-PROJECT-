#pragma once
/////////////////////////////////////////////////////
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <thread>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdint.h>
#include <cstdlib>
#include <mutex>
#include <math.h>
#include <string>
#include <intrin.h>
#include <stdio.h>
#include <assert.h>
#include <winternl.h>
#include <shlwapi.h>
#include <d3d11.h>
#include <d3dx11tex.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <vector>
#include <algorithm>
#include <ShlObj_core.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "D3DX11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
#include "../xor/xorstr.h"
#include "../unicode/unicode.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_internal.h"
#include "../json/json.h"
#include "../settings/settings.h"
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
ImFont* m_font;
using namespace std;
using namespace ImGui;
bool show_menu = true;
bool show_app_TeleportManager = false;
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
#include "../renderer/renderer.h"
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
#define get_key_down(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define get_key_up(vk_code)     ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
vector<string> split(const string &s, char delim)
{
	stringstream ss(s);
	string item;
	vector<string> elems;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

uintptr_t gmh(LPCWSTR lp_mod_name)
{
	return (uintptr_t)GetModuleHandleW(lp_mod_name);
}
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
#define VK_0				0x30
#define VK_1				0x31
#define VK_2				0x32
#define VK_3				0x33
#define VK_4				0x34
#define VK_5				0x35
#define VK_6				0x36
#define VK_7				0x37
#define VK_8				0x38
#define VK_9				0x39
#define VK_A				0x41
#define VK_B				0x42
#define VK_C				0x43
#define VK_D				0x44
#define VK_E				0x45
#define VK_F				0x46
#define VK_G				0x47
#define VK_H				0x48
#define VK_I				0x49
#define VK_J				0x4A
#define VK_K				0x4B
#define VK_L				0x4C
#define VK_M				0x4D
#define VK_N				0x4E
#define VK_O				0x4F
#define VK_P				0x50
#define VK_Q				0x51
#define VK_R				0x52
#define VK_S				0x53
#define VK_T				0x54
#define VK_U				0x55
#define VK_V				0x56
#define VK_W				0x57
#define VK_X				0x58
#define VK_Y				0x59
#define VK_Z				0x5A
#define VK_LSHIFT			0xA0
#define VK_RSHIFT			0xA1
#define VK_LCONTROL			0xA2
#define VK_RCONTROL			0xA3
#define VK_LMENU			0xA4
#define VK_RMENU			0xA5
#define VK_CAPS             0x14
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
void open_console()
{
	AllocConsole();
	freopen(xor_a("CONOUT$"), xor_a("w"), stdout);
}
/////////////////////////////////////////////////////

