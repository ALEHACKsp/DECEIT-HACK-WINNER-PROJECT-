#pragma once

struct _teleport_mg
{
	string sz_name_point;
	Vec3 v_point;
}teleport_mg;

vector<_teleport_mg> v_teleport;

class i_entity_spawn_params
{
public:
	int32 entity_id; //0x0000 
	char pad_0x0004[0x14]; //0x0004 
	i_entity_class* p_entity_class; //0x0018 
	char pad_0x0020[0x10]; //0x001C 
	const char* s_name; //0x0024 
	char pad_0x0038[0x8]; //0x0028 
	uint32 n_flags; //0x002C 
	char pad_0x0044[0x3]; //0x0030 
	Vec3 v_position; //0x0040 
	Quat q_rotation; //0x004C 
	Vec3 v_scale; //0x005C 
	char pad_0x00060[0x90]; //0x00060 
}; //Size=0x0068

struct s_spread_mod_params
{
	f32 min_mod;
	f32 max_mod;
	f32 attack_mod;
	f32 decay_mod;
	f32 end_decay_mod;
	f32 speed_m_mod;
	f32 speed_holdBreathActive_m_mod;
	f32 rotation_m_mod;
	f32 spread_crouch_m_mod;
	f32 spread_jump_m_mod;
	f32 spread_slide_m_mod;
	f32 spread_holdBreathActive_m_mod;
};

struct s_recoil_mod_params
{
	f32 max_recoil_mod;
	f32 attack_mod;
	f32 first_attack_mod;
	f32 decay_mod;
	f32 end_decay_mod;
	Vec2 max_mod;
	f32 impulse_mod;
	f32 recoil_crouch_m_mod;
	f32 recoil_jump_m_mod;
	f32 recoil_holdBreathActive_m_mod;
};

struct s_weapon_ammo
{
	i_entity_class* p_ammo_class;
	int32 count;
};

struct s_rwi_params
{
	char pad_0x0000[0x18]; //0x0000
	Vec3 dir; //0x0018 
	Vec3 org; //0x0024 
	int32 obj_types; //0x0030 
}; //Size=0x0840

struct s_collision_class
{
	uint32_t type;
	uint32_t ignore;

	s_collision_class() {}
	s_collision_class(uint32 t, uint32 i)
	{
		type = t;
		ignore = i;
	}
};

class i_physical_entity
{
public:
	s_char _0x0000[28];
	i_entity* get_entity; //0x001C 
};

struct ray_hit
{
	f32 dist;
	i_physical_entity* p_collider;
	int32 ipart;
	int32 part_id;
	int16 surface_idx;
	int16 idmat_drg;
	int32 foreign_idx;
	int32 i_node;
	Vec3 pt;
	Vec3 n;
	int32 b_terrain;
	int32 i_prim;
	ray_hit* next;
};

typedef s_weapon_ammo** t_ammo_vector;

#pragma pack(push, 4)
struct _target
{
	int32 p_result;
	Vec3 bone_hit_point;
} target;
#pragma pack(pop)