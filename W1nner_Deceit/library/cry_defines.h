#include "cry_sdk/cry_sdk.h"

/////////////////////////////////////
struct ray_hit;
struct ray_hit_cached;
struct ve_to_screen;
struct s_rwi_params;
struct hit_info;
class IXmlNode;
class XmlNodeRef;
class i_hardware_mouse;
class i_particle_effect;
class i_ffont;
class i_cry_font;
class i_texture;
class i_renderer;
class i_renderer_res;
class i_ui_draw;
class i_game_actor;
class i_game;
class i_console_var;
class i_console;
class i_equipment_manager;
class i_item_system;
class i_cry_action;
class i_script_table;
class i_script_system;
class i_physical_world;
class i_system;
class i_timer;
class i_entity_class_registry;
class i_entity_spawn_params;
class i_entity_system;
class i_entity_it;
class i_skeleteon_pose;
class i_skeleteon_pose_id;
class i_character_instance;
class i_actor_system;
class i_actor_iterator;
class i_entity_script_proxy;
class i_entity;
class i_entity_archetype;
class i_entity_class;
class i_entity_render_proxy;
class i_physical_entity;
class i_3d_engine;
class i_animation_graph_state;
class i_movement_controller;
struct i_coop_assist_message;
class i_game_object;
class i_actor;
class i_player;
class i_stamina;
class i_item;
class i_weapon;
class i_fire_mode;
class i_weapon_system;
class i_weapon_player;
class i_weapon_crypt;
class i_weapon_ammo;
class i_game_rules;
class i_cry_action;
class i_game_rules_system;
class i_game_rules;
class i_game_frame_work;
class i_cvar;
class i_movement_component;
struct e_event_rwi;
typedef void(*console_var_func)(i_console_var*);
/////////////////////////////////////
template <typename t>
t f_virtual(PVOID f_base, int64 f_index) 
{ 
	return (*(t**)f_base)[dev_8(f_index)];
}
/////////////////////////////////////
template <typename t>
t f_virtual_address(uint64 f_address)
{
	return (t)(gmh(0) + f_address);
}
/////////////////////////////////////
template <typename t>
static bool is_valid_ptr(t* ptr)
{
	return (ptr) ? true : false;
}
/////////////////////////////////////

/////////////////////////////////////
Vec3 m_head = { type_zero::_zero };
Vec3 v_head = { type_zero::_zero };
Vec3 v_camera = { type_zero::_zero };
const char* weapon_name = NULL;
/////////////////////////////////////

/////////////////////////////////////
typedef void(WINAPI* m_end_frame)(i_renderer* a1);
m_end_frame p_end_frame;
/////////////////////////////////////

/////////////////////////////////////
enum class e_c_var_type : signed __int64
{
	invalid = 0,
	t_int = 1,
	f_float = 2,
	f_string = 3,
	t_int64 = 4
};
/////////////////////////////////////

/////////////////////////////////////
enum e_entity_proxy
{
	entity_proxy_render,
	entity_proxy_physics,
	entity_proxy_script,
	entity_proxy_sound,
	entity_proxy_ai,
	entity_proxy_area,
	entity_proxy_boids,
	entity_proxy_boid_object,
	entity_proxy_camera,
	entity_proxy_flow_graph,
	entity_proxy_substitution,
	entity_proxy_trigger,
	entity_proxy_rope,
	entity_proxy_entity_node,
	entity_proxy_user,
	entity_proxy_last
};
/////////////////////////////////////

/////////////////////////////////////
enum rnd_flags
{
	e_all_map = 0x10,
	e_limit_distance = 0xFFFFFFEF
};
/////////////////////////////////////

/////////////////////////////////////
enum visible_flags
{
	e_line_sight = 0x0F,
	e_metal_sheets = 0x8,
	e_glass = 0xA
};

enum e_srwi_flags
{
	e_ammo_flags = 0x31F,
	e_ammo_wall_shot = 0x10,
	e_ammo_wall_shot_f = 0x75,
	e_ammo_wall_shot_e = 0x7E,
	e_ammo_wall_shot_o = 0x14,
	e_actors_flags = 0x100 | 1
};
/////////////////////////////////////

/////////////////////////////////////
Vec3 m_pos;
static int  point_selected = -1;
static char name_point[10] = "";
/////////////////////////////////////


