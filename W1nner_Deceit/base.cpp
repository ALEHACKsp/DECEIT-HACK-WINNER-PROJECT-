#include "stdafx/stdafx.h"
#include "hook/hook.h"
#include "library/cry_classes.h"
#include "library/cry_reversing.h"
#include "library/cry_hook/cry_hook.h"
#include "menu/menu.h"

HRESULT WINAPI h_present(IDXGISwapChain* p_swapchain, uint32_t syncintreval, uint32_t flags)
{
	im_gui_dx11_init(p_swapchain, xor_w(L"CryENGINE"));
	begin_frame();
	create_present_engine();
	create_circle_fov();
	end_frame();
	im_menu();
	ImGui::Render();
	return p_present(p_swapchain, syncintreval, flags);
}

void h_end_frame(i_renderer* a1)
{
	create_frame_engine();
	return p_end_frame(a1);
}

void present_hook(int64_t present, bool hook)
{
	static bool init_once = false;
	if (!init_once)
	{
		present_old = present_address;
		init_once = true;
	}

	if (hook)
	{
		p_present = (m_present)*(int64_t*)(present_address);
		*(int64_t*)(present_address) = present;
	}
	else
	{
		*(int64_t*)(present_address) = present_old;
	}
}

BOOL WINAPI DllMain(HINSTANCE h_instance, DWORD dw_reason, LPVOID lp_reserved)
{
	switch (dw_reason)
	{
	case DLL_PROCESS_ATTACH:			
		///////////////////////////////////////
		create_cfg.load_settings();
		///////////////////////////////////////

		///////////////////////////////////////
		present_hook((int64_t)h_present, true);
		///////////////////////////////////////

		///////////////////////////////////////
		p_end_frame_vmt = new c_vmt((uint64**)i_renderer::singleton());
		p_end_frame = (m_end_frame)p_end_frame_vmt->setup_hook((uint64)h_end_frame, virtual_renderer_res::f_end_frame);
		///////////////////////////////////////

		///////////////////////////////////////
		p_rwi_vmt = new c_vmt((uint64**)i_physical_world::singleton());
		p_rwi = (m_rwi)p_rwi_vmt->setup_hook((uint64)h_rwi, virtual_physical_world::f_s_rwi_ray_world_intersection);
		///////////////////////////////////////
		break;

	case DLL_PROCESS_DETACH:
		present_hook(0, false);
		p_end_frame_vmt->un_hook();
		p_rwi_vmt->un_hook();
		break;
	}
	return TRUE;
}