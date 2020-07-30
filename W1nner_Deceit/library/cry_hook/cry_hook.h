#pragma once

typedef int32(__fastcall* m_rwi)(i_physical_world*, s_rwi_params&, char*, int32);
m_rwi p_rwi = nullptr;

int32 __fastcall h_rwi(i_physical_world* a1, s_rwi_params& srwi, char* p_name_tag, int32 i)
{
	if (srwi.obj_types == e_srwi_flags::e_ammo_flags)
	{
		if (Settings::Aimbot::Enabled && target.p_result != 0)
		{
			if (Settings::Aimbot::WallShot)
				srwi.obj_types = e_srwi_flags::e_ammo_wall_shot_e;

			srwi.dir = target.bone_hit_point - srwi.org;
		}
	}

	return p_rwi(a1, srwi, p_name_tag, i);
}