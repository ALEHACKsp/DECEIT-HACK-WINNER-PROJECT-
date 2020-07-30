#pragma once
#include "cry_defines.h"
#include "cry_structs.h"

enum game_data : int32
{
	a_game_overlay_present = 0x194458, // "Hooking vtable for swap chain"
	a_console = 0x24868D8, // ‬cl_fov
	a_physical_world = 0x253D880, // RayWorldIntersection 
	a_renderer = 0x2486920, // GetCursorPos ‬‬ ‬
	a_renderer_res = 0x253D868, // ScreenShotHighRes ‬‬ ‬
	a_entity_system = 0x24868D0, // GetEntitiesByClass‬
	a_game_frame_work = 0x24868C0, // ‬‬[%s]: %s
};

enum virtual_console_var : int32
{
	f_get_i_val = 16,
	f_get_f_val = 32,
	f_get_string = 40,
	f_set_f = 32,
	f_set_i = 56,
	f_set_c = 64,
	f_get_type = 112,
};

enum virtual_physical_world : int32
{
	f_s_rwi_ray_world_intersection = 288, // RayWorldIntersection
	f_ray_world_intersection = 752,
};

enum virtual_renderer: int32
{
	f_project_to_screen = 560, // ProjectToScreen or behaviour
};

enum virtual_renderer_res : int32
{
	f_end_frame = 352, // ScreenShotHighRes
	f_get_width = 472, // ScreenShotHighRes
	f_get_height = 464, // ScreenShotHighRes
};

enum virtual_entity_class_registry : int32
{
	f_find_class = 24,
	f_register_std_class = 48,
};

enum virtual_entity_system : int32
{
	f_create_entity_iterator = 136, 
	f_get_class_registry = 64,
	f_remove_entity = 128,
	f_spawn_entity = 72,
};

enum virtual_entity_it : int32
{
	f_add_ref = 8, 
	f_release = 16, 
	f_is_end = 24, 
	f_entity_next = 32, 
	f_this = 40, 
	f_move_first = 48, 
};

enum virtual_entity : int32
{
	f_get_entity_id = 8,
	f_get_entity_class = 24, //"soclasses_SmartObjectClass"
	f_get_flags = 48,
	f_set_name = 120,
	f_get_name = 128, // "entity=%s slot=%d"
	f_is_hidden = 464, // "The actor %s is additionally saved as external entity." [GetId + GetName + IsHidden]
	f_get_world_tm = 248, // "%s ca_local_bb (%.4f %.4f %.4f) (%.4f %.4f %.4f)"
	f_get_world_bounds = 272, // GetProjectedWorldBBox
	f_set_pos = 296, // SetLocalPos pseudocode
	f_get_pos = 304,
	f_set_scale = 328, // SetLocalScale pseudocode
	f_get_character = 976, // "Bip01 Pelvis" ctrl + x -> [2]
	f_get_proxy = 928, // "Material Parameter: %s is not valid material parameter name for material %s"
	f_load_geometry = 1032, // EntityLinks
	//rnd flags: 0x38 [nomaterial_vehicle]
};

enum virtual_actor_system : int32
{
	f_get_actor = 24,
	f_get_actor_count = 48,
	f_create_actor_iterator = 56,
};

enum virtual_actor_iterator : int32
{
	f_size = 8,
	f_actor_next = 16,
};

enum virtual_game_frame_work : int32
{
	f_get_client_actor = 536, // "_LocalPlayer" [GameFrameWork + GetClientActor]
	f_get_client_actor_id = f_get_client_actor + 0x8,
	f_get_client_entity = f_get_client_actor_id + 0x8,
	f_get_client_entity_id = f_get_client_entity + 0x8,
	f_get_game_rules_system = 264, // CGameServerNub::CreateChannel() assigning actor %u '%s' to channel %u
};

enum virtual_game_rules_system : int32
{
	f_get_game_rules = 80,
};

enum virtual_game_rules : int32
{
	f_set_channel_for_migrating_player = 608,
};

enum virtual_skeleteon_pose : int32
{
	f_get_joint_id_by_name = 72, // Bip01 Pelvis -> [2]
	f_get_abs_joint_by_id = 192, // Bip01 Pelvis -> [2]
};

enum virtual_character_instance : int32
{
	f_get_skeleton_pose = 168, // "Bip01 Pelvis" ctrl + x -> [2]
	f_get_skeleton_pose_id = 136, // "Bip01 Pelvis" ctrl + x -> [2]
};

enum virtual_actor : int32
{
	f_get_health = 312, // CFlowActorSetHealth - No Entity or Entity not an actor!
	f_set_health = 320,
	f_is_dead = 384, // Saving failed : player is dead!
	f_get_view_rotation = 504,
	f_set_view_rotation = 512,
	f_get_current_item = 568, // CurrentItemName
};

enum virtual_item : int32
{
	f_get_weapon = 720, // %s: Weapon not available (EntId %i)
};

enum virtual_fire_mode : int32
{
	f_set_spread_param = 496,
	f_set_recoil_param = 512,
	f_start_fire_fm = 216,
	f_stop_fire_fm = 224,
	f_is_fire = 232,
	f_net_shoot = 296,
};

enum virtual_weapon : int32
{
	f_get_ammo_count = 200,
	f_set_ammo_count = 208,
	f_start_fire = 96, //%s: Weapon not available (EntId %i)
	f_stop_fire = 104,
};

template <typename t>
void get_class_tables_list(const char* class_name, t class_point, bool show_original_number = false, uint64 base_address_dump = 0)
{
	uint64 adr = 0;
	uint32 number = 0;
	uint64 adr_m_b = 0;
	uint64 adr_p_b = 0;
	uint64 p_class = (uint64)class_point;
	cout << class_name << endl;
	uint64 point = *(uint64*)(p_class);

	while (*(uint64*)(point + number * sizeof(uint64)))
	{
		if (base_address_dump != 0)
		{
			adr = *(uint64*)(point + number * sizeof(uint64));
			adr_m_b = adr - gmh(0);
			adr_p_b = base_address_dump + adr_m_b;
		}

		if (base_address_dump == 0)
		{
			adr_p_b = *(uint64*)(point + number * sizeof(uint64));
		}

		cout << dec << number;

		if (show_original_number)
			cout << "|" << dec << number * 8;

		cout << "| 0x" << hex << adr_p_b << endl;
		++number;
	}
}

Vec2 get_window_size()
{
	Vec2 window_size;
	RECT window_rect = { 0 };
	GetClientRect(FindWindowW(xor_w(L"CryENGINE"), 0), &window_rect);

	window_size.x = (f32)window_rect.right;
	window_size.y = (f32)window_rect.bottom;
	return window_size;
}

uintptr_t present_address = gmh(xor_w(L"GameOverlayRenderer64.dll")) + game_data::a_game_overlay_present;

class i_console
{
public:
	static i_console* singleton()
	{
		return *(i_console**)(gmh(0) + game_data::a_console);
	}

	i_console_var* register_int(const char* s_name, int i_value, int n_flags, const char* help = "", console_var_func p_change_func = 0)
	{
		return f_virtual<i_console_var*(__fastcall*)(PVOID, const char*, int, int, const char*, console_var_func)>(this, 528)(this, s_name, i_value, n_flags, help, p_change_func);
	}

	void execute_string(const char* command, const bool b_silent_mode = false, const bool b_defer_execution = false)
	{
		return f_virtual<void(__fastcall*)(PVOID, const char*, const bool, const bool)>(this, 280)(this, command, b_silent_mode, b_defer_execution);
	}

	//e_DebugDraw + getcvar->
	i_console_var* get_cvar(const char* name)
	{
		return f_virtual<i_console_var*(__fastcall*)(PVOID, const char*)>(this, 120)(this, name);
	}
};

class i_console_var
{
public:
	int get_i_val()
	{
		return f_virtual<int(__fastcall*)(PVOID)>(this, virtual_console_var::f_get_i_val)(this);
	}

	float get_f_val()
	{
		return f_virtual<float(__fastcall*)(PVOID)>(this, virtual_console_var::f_get_f_val)(this);
	}

	const char* get_string()
	{
		return f_virtual<const char*(__fastcall*)(PVOID)>(this, virtual_console_var::f_get_string)(this);
	}

	void set(const float f)
	{
		return f_virtual<void(__fastcall*)(PVOID, const float)>(this, virtual_console_var::f_set_f)(this, f);
	}

	void set(const int i)
	{
		return f_virtual<void(__fastcall*)(PVOID, const int)>(this, virtual_console_var::f_set_i)(this, i);
	}

	void set(const char* s)
	{
		return f_virtual<void(__fastcall*)(PVOID, const char*)>(this, virtual_console_var::f_set_c)(this, s);
	}

	template<typename type>
	type get_val() 
	{
		return **(type**)(this + 0x48);
	}

	template<typename type>
	void set_val(type value) 
	{
		**(type**)(this + 0x48) = value;
	}

	void* value_ptr() 
	{
		return *(void**)(this + 0x48);
	}

	e_c_var_type get_type()
	{
		return f_virtual<e_c_var_type(__fastcall*)(void*)>(this, virtual_console_var::f_get_type)(this);
	}

	void* vftable;
	char* str_name; //0x0008 
	char* str_desciption; //0x0010 
};

class i_renderer
{
public:
	static i_renderer* singleton()
	{
		return *(i_renderer**)(gmh(0) + game_data::a_renderer);
	}
	
	bool project_to_screen(f32 ptx, f32 pty, f32 ptz, f32* sx, f32* sy, f32* sz)
	{
		f_virtual<bool(__fastcall*)(PVOID, f32, f32, f32, f32*, f32*, f32*)>(this, virtual_renderer::f_project_to_screen)(this, ptx, pty, ptz, sx, sy, sz);

		*sx *= (get_window_size().x / 100.0f);
		*sy *= (get_window_size().y / 100.0f);
		*sz *= 1.0f;

		return (*sz < 1.0f);
	}

	bool world_to_screen(Vec3 in, Vec3* out)
	{
		f32 x, y, z;

		if (!project_to_screen(in.x, in.y, in.z, &x, &y, &z))
			return false;

		out->x = x;
		out->y = y;
		out->z = z;

		return true;
	}
};

class i_renderer_res
{
public:
	static i_renderer_res* singleton()
	{
		return *(i_renderer_res**)(gmh(0) + game_data::a_renderer_res);
	}

	void end_frame()
	{
		return f_virtual<void(__fastcall*)(PVOID)>(this, virtual_renderer_res::f_end_frame)(this);
	}

	int32 get_width()
	{
		return f_virtual<int32(__fastcall*)(void*)>(this, virtual_renderer_res::f_get_width)(this);
	}

	int32 get_height()
	{
		return f_virtual<int32(__fastcall*)(void*)>(this, virtual_renderer_res::f_get_height)(this);
	}
};

class i_physical_world
{
public:
	static i_physical_world* singleton()
	{
		return *(i_physical_world**)(gmh(0) + game_data::a_physical_world);
	}

	int32 s_rwi_ray_world_intersection(s_rwi_params& rp, c_char p_name_tag, int32 i_caller)
	{
		return f_virtual<int32(__fastcall*)(PVOID, s_rwi_params&, c_char, int32)>(this, virtual_physical_world::f_s_rwi_ray_world_intersection)(this, rp, p_name_tag, i_caller);
	}

	int32 ray_world_intersection(const Vec3& org, const Vec3& dir, int32 obj_types, uint32 flags, ray_hit* hits, int32 n_max_hits, i_physical_entity** p_skip_ents = 0, int32 n_skip_ents = 0, void* p_foreign_data = 0, int32 i_foreign_data = 0, c_char p_name_tag = xor_a("RayWorldIntersection(Game)"), ray_hit_cached* p_hit_Last = 0, int32 i_caller = 4)
	{
		return f_virtual<int32(__fastcall*)(PVOID, const Vec3&, const Vec3&, int32, uint32, ray_hit*, int32, i_physical_entity**, int32, void*, int32, c_char, ray_hit_cached*, int32)>(this, virtual_physical_world::f_ray_world_intersection)(this, org, dir, obj_types, flags, hits, n_max_hits, p_skip_ents, n_skip_ents, p_foreign_data, i_foreign_data, p_name_tag, p_hit_Last, i_caller);
	}
};

class i_entity_class_registry
{
public:
	i_entity_class* find_class(const char* s_class_name)
	{
		return f_virtual<i_entity_class*(__fastcall*)(PVOID, const char*)>(this, virtual_entity_class_registry::f_find_class)(this, s_class_name);
	}

	i_entity_class* register_std_class(const i_entity_spawn_params& entity_class_desc)
	{
		return f_virtual<i_entity_class*(__fastcall*)(PVOID, const i_entity_spawn_params&)>(this, virtual_entity_class_registry::f_register_std_class)(this, entity_class_desc);
	}
};

class i_entity_system
{
public:
	static i_entity_system* singleton()
	{
		return *(i_entity_system**)(gmh(0) + game_data::a_entity_system);
	}

	void create_entity_iterator(i_entity_it** entity_iterator)
	{
		return f_virtual<void(__fastcall*)(PVOID, i_entity_it**)>(this, virtual_entity_system::f_create_entity_iterator)(this, entity_iterator);
	}

	i_entity_class_registry* get_class_registry()
	{
		return f_virtual<i_entity_class_registry*(__fastcall*)(PVOID)>(this, virtual_entity_system::f_get_class_registry)(this);
	}

	void remove_entity(int32 entity, bool b_force_remove_now = false)
	{
		f_virtual<void(__fastcall*)(PVOID, int32, bool)>(this, virtual_entity_system::f_remove_entity)(this, entity, b_force_remove_now);
	}

	i_entity* spawn_entity(i_entity_spawn_params& params, bool b_auto_init = true)
	{
		return f_virtual<i_entity*(__fastcall*)(PVOID, i_entity_spawn_params&, bool)>(this, virtual_entity_system::f_spawn_entity)(this, params, b_auto_init);
	}

	i_entity* spawn_object(const char* entity_name, const char* entity_class, Vec3 v_pos)
	{
		if (i_entity_class* p_class = get_class_registry()->find_class(entity_class))
		{
			i_entity_spawn_params spawn_params;
			memset(&spawn_params, 0, sizeof(i_entity_spawn_params));
			spawn_params.v_position = v_pos;
			spawn_params.s_name = entity_name;
			spawn_params.p_entity_class = p_class;
			spawn_params.q_rotation.w = 1.f;
			spawn_params.v_scale = Vec3(1.f, 1.f, 1.f);
			return spawn_entity(spawn_params);
		}
		return nullptr;
	}
};

class i_entity_it
{
public:
	void add_ref()
	{
		return f_virtual<void(__fastcall*)(PVOID)>(this, virtual_entity_it::f_add_ref)(this);
	}

	void release()
	{
		return f_virtual<void(__fastcall*)(PVOID)>(this, virtual_entity_it::f_release)(this);
	}

	bool is_end()
	{
		return f_virtual<bool(__fastcall*)(PVOID)>(this, virtual_entity_it::f_is_end)(this);
	}

	i_entity* entity_next()
	{
		return f_virtual<i_entity*(__fastcall*)(PVOID)>(this, virtual_entity_it::f_entity_next)(this);
	}

	i_entity* entity_this()
	{
		return f_virtual<i_entity*(__fastcall*)(PVOID)>(this, virtual_entity_it::f_this)(this);
	}

	void move_first()
	{
		return f_virtual<void(__fastcall*)(PVOID)>(this, virtual_entity_it::f_move_first)(this);
	}
};

class i_entity
{
public:
	char pad_0x0000[0x120]; //0x0000
	Vec3 v_position; //0x0120 
	char pad_0x012C[0x8]; //0x012C
	Matrix34 m_world_tm; //0x0134 
	char pad_0x0174[0x8A8]; //0x0174

	template<class data>
	data get_entity_function(int32 dw_offset)
	{
		return *(data*)(this + dw_offset);
	}

	template<class data>
	void set_entity_function(int32 dw_offset, data value)
	{
		*(data*)(this + dw_offset) = value;
	}

	int32 get_entity_id()
	{
		return f_virtual<int32(__fastcall*)(void*)>(this, virtual_entity::f_get_entity_id)(this);
	}

	i_entity_class* get_entity_class()
	{
		return f_virtual<i_entity_class*(__fastcall*)(PVOID)>(this, virtual_entity::f_get_entity_class)(this);
	}

	bool is_hidden()
	{
		return f_virtual<bool(__fastcall*)(PVOID)>(this, virtual_entity::f_is_hidden)(this);
	}

	int get_flags()
	{
		return f_virtual<int(__fastcall*)(PVOID)>(this, virtual_entity::f_get_flags)(this);
	}

	void get_world_bounds(AABB& bbox)
	{
		return f_virtual<void(__fastcall*)(PVOID, AABB&)>(this, virtual_entity::f_get_world_bounds)(this, bbox);
	}

	Matrix34& get_world_tm()
	{
		return f_virtual<Matrix34&(__fastcall*)(PVOID)>(this, virtual_entity::f_get_world_tm)(this);
	}

	i_character_instance* get_character(uint64 n_slot)
	{
		return f_virtual<i_character_instance*(__fastcall*)(PVOID, uint64)>(this, virtual_entity::f_get_character)(this, n_slot);
	}

	i_entity_render_proxy* get_proxy_render(e_entity_proxy proxy = e_entity_proxy::entity_proxy_render)
	{
		return f_virtual<i_entity_render_proxy*(__fastcall*)(PVOID, e_entity_proxy)>(this, virtual_entity::f_get_proxy)(this, proxy);
	}

	i_entity_render_proxy* create_render_proxy(e_entity_proxy proxy = e_entity_proxy::entity_proxy_render)
	{
		return f_virtual_address<i_entity_render_proxy*(__fastcall*)(PVOID, e_entity_proxy)>(0x7EB9F)(this, proxy);
	}

	void set_pos(Vec3 v_pos)
	{
		return f_virtual<void(__fastcall*)(void*, Vec3*)>(this, virtual_entity::f_set_pos)(this, &v_pos);
	}

	Vec3& get_pos()
	{
		return f_virtual<Vec3&(__fastcall*)(PVOID)>(this, virtual_entity::f_get_pos)(this);
	}

	void set_scale(Vec3 v_scale)
	{
		return f_virtual<void(__fastcall*)(void*, Vec3*)>(this, virtual_entity::f_set_scale)(this, &v_scale);
	}

	const char* get_name()
	{
		return f_virtual<const char*(__fastcall*)(PVOID)>(this, virtual_entity::f_get_name)(this);
	}

	void set_name(const char* name)
	{
		return f_virtual<void(__fastcall*)(PVOID, const char*)>(this, virtual_entity::f_set_name)(this, name);
	}

	int load_geometry(int n_slot, const char* s_file_name, const char* s_geom_name, int n_load_flags)
	{
		return f_virtual<int(__fastcall*)(PVOID, int, const char*, const char*, int)>(this, virtual_entity::f_load_geometry)(this, n_slot, s_file_name, s_geom_name, n_load_flags);
	}
};

class i_entity_render_proxy
{
public:
	char pad_0x0000[0x38]; //0x0000
	__int32 rnd_flags; //0x0038 524544
	char pad_0x003C[0x14]; //0x003C
	__int32 vision_color; //0x0050 
	char pad_0x0054[0x890]; //0x0054

	void set_hud_silhouettes_vision(bool b_all_map)
	{
		b_all_map ? rnd_flags |= rnd_flags::e_all_map : rnd_flags &= rnd_flags::e_limit_distance;
	}

	void set_hud_silhouettes_params(f32 r, f32 g, f32 b, f32 a)
	{
		int32 m_color = (int32)(f32)(a * 255.0) | (((int32)(f32)(b * 255.0) | (((int32)(f32)(g * 255.0) | ((int32)(f32)(r * 255.0) << 8)) << 8)) << 8);
		vision_color = m_color;
	}
};

class i_entity_class
{
public:
	const char* get_class_name() 
	{
		return f_virtual<const char*(__fastcall*)(void*)>(this, 16)(this);
	}
};

class i_skeleteon_pose
{
public:
	int16 get_joint_id_by_name(c_char sz_joint_name)
	{
		return f_virtual<int16(__fastcall*)(PVOID, c_char)>(this, virtual_skeleteon_pose::f_get_joint_id_by_name)(this, sz_joint_name);
	}
};

class i_skeleteon_pose_id
{
public:
	QuatT& get_abs_joint_by_id(int16 n_joint_id)
	{
		return f_virtual<QuatT&(__fastcall*)(PVOID, int16)>(this, virtual_skeleteon_pose::f_get_abs_joint_by_id)(this, n_joint_id);
	}
};

class i_character_instance
{
public:
	i_skeleteon_pose* get_skeleton_pose()
	{
		return f_virtual<i_skeleteon_pose*(__fastcall*)(PVOID)>(this, virtual_character_instance::f_get_skeleton_pose)(this);
	}

	i_skeleteon_pose_id* get_skeleteon_pose_id()
	{
		return f_virtual<i_skeleteon_pose_id*(__fastcall*)(PVOID)>(this, virtual_character_instance::f_get_skeleton_pose_id)(this);
	}
};

class i_actor
{
public:	
	template<class data>
	data get_actor_function(int32 dw_offset)
	{
		return *(data*)(this + dw_offset);
	}

	template<class data>
	void set_actor_function(int32 dw_offset, data value)
	{
		*(data*)(this + dw_offset) = value;
	}

	i_entity* get_entity()
	{
		return *(i_entity**)(this + 0x10);
	}

	int32 get_entity_id()
	{
		return *(int32*)(this + 0x20);
	}

	f32 get_health()
	{
		return f_virtual<f32(__fastcall*)(PVOID)>(this, virtual_actor::f_get_health)(this);
	}

	void set_health(f32 health)
	{
		return f_virtual<void(__fastcall*)(PVOID, float)>(this, virtual_actor::f_set_health)(this, health);
	}

	bool is_dead()
	{
		return f_virtual<bool(__fastcall*)(PVOID)>(this, virtual_actor::f_is_dead)(this);
	}

	Quat get_view_rotation()
	{
		return f_virtual<Quat(__fastcall*)(PVOID)>(this, virtual_actor::f_get_view_rotation)(this);
	}

	void set_view_rotation(const Quat& rotation)
	{
		return f_virtual<void(__fastcall*)(PVOID, const Quat&)>(this, virtual_actor::f_set_view_rotation)(this, rotation);
	}

	i_item* get_current_item(bool include_vehicle = false)
	{
		return f_virtual<i_item*(__fastcall*)(PVOID, bool)>(this, virtual_actor::f_get_current_item)(this, include_vehicle);
	}
};

class i_item
{
public:
	i_weapon* get_weapon()
	{
		return f_virtual<i_weapon*(__fastcall*)(void*)>(this, virtual_item::f_get_weapon)(this);
	}

	i_entity* get_weapon_entity()
	{
		return *(i_entity**)(this + 0x10);
	}
};

struct i_fire_mode 
{
	f32 __fastcall get_fire_rate()
	{
		return (f32) * (int16*)(*(uint64*)(*(uint64*)(this + 0x10) + 8) + 0x90);
	}

	void set_fire_rate(int16 r)
	{
		*(int16*)(*(uint64*)(*(uint64*)(this + 0x10) + 8) + 0x92) = r;
	}

	void set_spread_param(s_spread_mod_params* s_smp, f32 mod_multiplier)
	{
		f_virtual<void(__fastcall*)(void*, s_spread_mod_params*, f32)>(this, virtual_fire_mode::f_set_spread_param)(this, s_smp, mod_multiplier);
	}

	void set_recoil_param(s_recoil_mod_params* s_rmp, f32 mod_multiplier) 
	{
		f_virtual<void(__fastcall*)(void*, s_recoil_mod_params*, f32)>(this, virtual_fire_mode::f_set_recoil_param)(this, s_rmp, mod_multiplier);
	}

	void start_fire() 
	{
		f_virtual<void(__fastcall*)(void*)>(this, virtual_fire_mode::f_start_fire_fm)(this);
	}

	void stop_fire() 
	{
		f_virtual<void(__fastcall*)(void*)>(this, virtual_fire_mode::f_stop_fire_fm)(this);
	}

	bool is_fire() 
	{
		return f_virtual<bool(__fastcall*)(void*)>(this, virtual_fire_mode::f_is_fire)(this);
	}

	void net_shoot(Vec3* bullshit, int bullshit2) 
	{
		f_virtual<void(__fastcall*)(void*, Vec3*, int)>(this, virtual_fire_mode::f_net_shoot)(this, bullshit, bullshit2);
	}

	char pad_0x0000[0x90]; //0x0000
	f32 N000000FA; //0x0090 
	char pad_0x0094[0x14]; //0x0094
	f32 N000000FD; //0x00A8 
	char pad_0x00AC[0x74]; //0x00AC
	f32 fl_min_spread; //0x0120 
	f32 fl_max_spread; //0x0124 
};

class i_weapon 
{
public:
	int32 get_ammo_count(i_entity_class* type)
	{
		return f_virtual<int32(__fastcall*)(void*, i_entity_class*)>(this, virtual_weapon::f_get_ammo_count)(this, type);
	}

	void set_ammo_count(i_entity_class* type, int32 count)
	{
		return f_virtual<void(__fastcall*)(void*, i_entity_class*, int32)>(this, virtual_weapon::f_start_fire)(this, type, count);	
	}

	void start_fire_to_vector()
	{
		return f_virtual<void(__fastcall*)(void*)>(this, virtual_weapon::f_start_fire)(this);
	}

	void start_fire()
	{
		return f_virtual<void(__fastcall*)(void*)>(this, virtual_weapon::f_start_fire)(this);
	}

	void stop_fire()
	{
		return f_virtual<void(__fastcall*)(void*)>(this, virtual_weapon::f_stop_fire)(this);
	}

	char pad_0x0000[0x38]; //0x0000
	i_fire_mode* m_fm; //0x0038 
	char pad_0x0040[0xA0]; //0x0040
	s_weapon_ammo* m_ammo; //0x00E0 
	s_weapon_ammo* m_bonusammo; //0x00E8 
	unsigned char m_fire_alternation; //0x00F0 
	unsigned char m_restart_zoom; //0x00F1 
};

class i_actor_system
{
public:
	i_actor* get_actor(uint32 entity_id)
	{
		return f_virtual<i_actor*(__fastcall*)(PVOID, uint32)>(this, virtual_actor_system::f_get_actor)(this, entity_id);
	}
	
	int32 get_actor_count()
	{
		return f_virtual<int(__fastcall*)(PVOID)>(this, virtual_actor_system::f_get_actor_count)(this);
	}

	void create_actor_iterator(i_actor_iterator** actor_iterator)
	{
		return f_virtual<void(__fastcall*)(PVOID, i_actor_iterator**)>(this, virtual_actor_system::f_create_actor_iterator)(this, actor_iterator);
	}
};

class i_actor_iterator
{
public:
	int32 size()
	{
		return f_virtual<int(__fastcall*)(PVOID)>(this, virtual_actor_iterator::f_size)(this);
	}
	
	i_actor* actor_next()
	{
		return f_virtual<i_actor*(__fastcall*)(PVOID)>(this, virtual_actor_iterator::f_actor_next)(this);
	}
};

class i_ui_draw
{
public:
	void pre_render()
	{
		return f_virtual<void(__thiscall*)(PVOID)>(this, 16)(this);
	}

	void post_render()
	{
		return f_virtual<void(__thiscall*)(PVOID)>(this, 24)(this);
	}

	uint32 get_color_argb(uint8 uc_alpha, uint8 uc_red, uint8 uc_green, uint8 uc_blue)
	{
		return f_virtual<uint32_t(__thiscall*)(PVOID, uint8, uint8, uint8, uint8)>(this, 32)(this, uc_alpha, uc_red, uc_green, uc_blue);
	}

	int32 create_texture(const char* str_name, bool dont_release = true)
	{
		return f_virtual<int32(__thiscall*)(PVOID, const char*, bool)>(this, 40)(this, str_name, dont_release);
	}

	bool delete_texture(int32 i_texture_id)
	{
		return f_virtual<bool(__thiscall*)(PVOID, int32)>(this, 48)(this, i_texture_id);
	}

	void get_texture_size(int32 i_texture_id, f32& rf_size_x, f32& rf_size_y)
	{
		return f_virtual<void(__thiscall*)(PVOID, int32, f32&, f32&)>(this, 56)(this, i_texture_id, rf_size_x, rf_size_y);
	}

	void draw_triangle(f32 f_x0, f32 f_y0, f32 f_x1, f32 f_y1, f32 f_x2, f32 f_y2, uint32 ui_color)
	{
		return f_virtual<void(__thiscall*)(PVOID, f32, f32, f32, f32, f32, f32, uint32)>(this, 64)(this, f_x0, f_y0, f_x1, f_y1, f_x2, f_y2, ui_color);
	}

	void draw_line(f32 f_x1, f32 f_y1, f32 f_x2, f32 f_y2, uint32 ui_diffuse)
	{
		return f_virtual<void(__thiscall*)(PVOID, f32, f32, f32, f32, uint32)>(this, 72)(this, f_x1, f_y1, f_x2, f_y2, ui_diffuse);
	}

	void draw_quad_simple(f32 f_x, f32 f_y, f32 f_size_x, f32 f_size_y, uint32 ui_diffuse, int32 i_texture_id = 0)
	{
		return f_virtual<void(__thiscall*)(PVOID, f32, f32, f32, f32, uint32, int32)>(this, 80)(this, f_x, f_y, f_size_x, f_size_y, ui_diffuse, i_texture_id);
	}

	void draw_border_simple(f32 fx, f32 fy, f32 fw, f32 fh, f32 f_size, uint32 ui_diffuse)
	{
		draw_quad_simple(fx, fy, f_size, fh, ui_diffuse);
		draw_quad_simple(fx, fy + fh, fw, f_size, ui_diffuse);
		draw_quad_simple(fx, fy, fw, f_size, ui_diffuse);
		draw_quad_simple(fx + fw, fy, f_size, fh + f_size, ui_diffuse);
	}
};

class i_item_system
{
public:
	int32 give_item(i_actor* p_actor, c_char item, bool sound = false, bool select = false, bool keep_history = false, c_char setup = 0)
	{
		return f_virtual<int32(__fastcall*)(PVOID, i_actor*, c_char, bool, bool, bool, c_char)>(this, 272)(this, p_actor, item, sound, select, keep_history, setup);
	}

	void set_actor_item_by_name(i_actor* p_actor, c_char name, bool keep_history = true)
	{
		return f_virtual<void(__fastcall*)(PVOID, i_actor*, c_char, bool)>(this, 280)(this, p_actor, name, keep_history);
	}
	
	//Player_Default
	i_equipment_manager* get_equipment_manager()
	{
		return f_virtual<i_equipment_manager*(__fastcall*)(PVOID)>(this, 336)(this);
	}
};

class i_equipment_manager
{
public:
	bool give_equipment_pack(i_actor* p_actor, c_char pack_name, bool b_add, bool b_select_primary)
	{
		return f_virtual<bool(__fastcall*)(PVOID, i_actor*, c_char, bool, bool)>(this, 40)(this, p_actor, pack_name, b_add, b_select_primary);
	}
};

class i_game_rules_system
{
public:
	i_game_rules* get_game_rules()
	{
		return f_virtual<i_game_rules*(__fastcall*)(PVOID)>(this, virtual_game_rules_system::f_get_game_rules)(this);
	}
};

class i_game_frame_work
{
public:
	static i_game_frame_work* singleton()
	{
		return *(i_game_frame_work**)(gmh(0) + game_data::a_game_frame_work);
	}

	i_actor* get_client_actor()
	{
		return f_virtual<i_actor*(__fastcall*)(PVOID)>(this, virtual_game_frame_work::f_get_client_actor)(this);
	}

	int32 get_client_actor_id()
	{
		return f_virtual<int32(__fastcall*)(void*)>(this, virtual_game_frame_work::f_get_client_actor_id)(this);
	}

	i_entity* get_client_entity()
	{
		return f_virtual<i_entity*(__fastcall*)(PVOID)>(this, virtual_game_frame_work::f_get_client_entity)(this);
	}

	int32 get_client_entity_id()
	{
		return f_virtual<int32(__fastcall*)(void*)>(this, virtual_game_frame_work::f_get_client_entity_id)(this);
	}

	i_game_rules_system* get_game_rules_system()
	{
		return f_virtual<i_game_rules_system*(__fastcall*)(PVOID)>(this, virtual_game_frame_work::f_get_game_rules_system)(this);
	}

	//Снизу "CustomEventManager" -> "ActorSystem"
	i_actor_system* get_actor_system()
	{
		return *(i_actor_system**)((int64)this + 0x4D8);
	}

	//ItemSystem
	i_item_system* get_item_system()
	{
		return *(i_item_system**)((int64)this + 0x4E0);
	}

	//UIDraw
	i_ui_draw* get_ui_draw()
	{
		return *(i_ui_draw**)((int64)this + 0x520);
	}
};

