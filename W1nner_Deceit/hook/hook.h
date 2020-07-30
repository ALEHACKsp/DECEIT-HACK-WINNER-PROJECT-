#pragma once

ID3D11Device* g_pdevice = nullptr;
ID3D11DeviceContext* g_pcontext = nullptr;
ID3D11RenderTargetView* g_prendertargetview = nullptr;
WNDPROC o_wndproc = nullptr;
HWND game_hwnd = nullptr;
std::once_flag wndproc;

typedef HRESULT(WINAPI* m_present)(IDXGISwapChain* p_swapchain, uint32_t syncintreval, uint32_t flags);
m_present p_present;
uintptr_t present_old = 0;

LRESULT WINAPI hk_wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	std::call_once(wndproc, [&] {/*std::cout << ("hooked wndproc") << std::endl;*/ });

	if (uMsg == WM_KEYDOWN) 
	{
		if (wParam == VK_INSERT)
			show_menu = !show_menu;
	}

	if (show_menu)
		ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);

	return CallWindowProc(o_wndproc, hwnd, uMsg, wParam, lParam);
}

string get_font_by_name(string font_name)
{
	string path_font;
	char sz_dir_system[256];
	GetWindowsDirectory(sz_dir_system, 256);
	path_font = (string(sz_dir_system) + xor_a("\\Fonts\\") + font_name);
	return path_font;
}

void im_gui_dx11_init(IDXGISwapChain* p_swapchain, LPCWSTR window_class_name)
{
	static bool init = false;
	if (!init && SUCCEEDED(p_swapchain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pdevice)))
	{
		game_hwnd = FindWindowW(window_class_name, 0);
		if (game_hwnd)
		{
			p_swapchain->GetDevice(__uuidof(g_pdevice), (void**)&g_pdevice);
			g_pdevice->GetImmediateContext(&g_pcontext);
			ID3D11Texture2D* p_back_buffer;
			p_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&p_back_buffer);
			g_pdevice->CreateRenderTargetView(p_back_buffer, NULL, &g_prendertargetview);
			o_wndproc = (WNDPROC)(SetWindowLongPtrW(game_hwnd, GWLP_WNDPROC, reinterpret_cast<uintptr_t>(hk_wndproc)));
			ImGui_ImplDX11_Init(game_hwnd, g_pdevice, g_pcontext);
			ImGui_ImplDX11_CreateDeviceObjects();

			ImFontConfig imst;
			ImGui::GetIO().Fonts->AddFontFromFileTTF(get_font_by_name(xor_a("Tahoma.TTF")).c_str(), 18.0f, &imst, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
			m_default_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(get_font_by_name(xor_a("Tahoma.TTF")).c_str(), 20.0f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		}

		init = true;
	}

	g_pcontext->OMSetRenderTargets(1, &g_prendertargetview, NULL);
}

////////////////////////
#define devision(c)       c/8
////////////////////////

////////////////////////
class c_vmt
{
public:
	c_vmt()
	{
		memset(this, 0, sizeof(c_vmt));
	}
	c_vmt(PDWORD64* p_base)
	{
		initialize(p_base);
	}
	~c_vmt()
	{
		un_hook();
	}
	bool initialize(PDWORD64* p_base)
	{
		p_table = p_base;
		old_fun = *p_base;
		c_table = get_count(*p_base);
		new_fun = new DWORD64[c_table];
		memcpy(new_fun, old_fun, sizeof(DWORD64) * c_table);
		*p_base = new_fun;
		return true;
	}
	bool initialize(PDWORD64** p_base)
	{
		return initialize(*p_base);
	}
	void un_hook()
	{
		if (p_table)
		{
			*p_table = old_fun;
		}
	}
	void re_hook()
	{
		if (p_table)
		{
			*p_table = new_fun;
		}
	}
	DWORD64 setup_hook(DWORD64 new_function, unsigned int i)
	{
		if (new_fun && old_fun && devision(i) <= c_table && devision(i) >= 0)
		{
			new_fun[devision(i)] = new_function;
			return old_fun[devision(i)];
		}
		return NULL;
	}
private:
	DWORD get_count(PDWORD64 p_vmt)
	{
		DWORD i = 0;
		for (i = 0; p_vmt[i]; i++)
		{
			if (IsBadCodePtr((FARPROC)p_vmt[i]))
				break;
		}
		return i;
	}
	DWORD	  c_table;
	PDWORD64* p_table;
	PDWORD64  new_fun;
	PDWORD64  old_fun;
};
////////////////////////

c_vmt* p_end_frame_vmt = nullptr;
c_vmt* p_rwi_vmt = nullptr;