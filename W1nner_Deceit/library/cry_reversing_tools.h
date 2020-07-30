#pragma once
#include "cry_classes.h"

bool elimination_actor(i_actor* m_actor, i_actor* p_actor)
{
	return (p_actor != m_actor);
}

bool key_manager_to_function(int32 key_active_id)
{
	if (key_active_id == 0) return true;
	else if (get_key_down(key_active_id)) return true;

	return false;
}

void start_shots(i_weapon* m_weapon, bool status)
{
	if (status)
	{
		m_weapon->start_fire();
		m_weapon->stop_fire();
	}
}

int32 is_visible(Vec3 v_pos)
{
	ray_hit tmp_hit;
	return i_physical_world::singleton()->ray_world_intersection(v_head, v_pos - v_head, 0x100 | 1, visible_flags::e_glass | 0x400, &tmp_hit, 1);
}

f32 calculate_distance(Vec3 pos_a, Vec3 pos_b)
{
	f32 d_x = pos_a.x - pos_b.x;
	f32 d_y = pos_a.y - pos_b.y;
	f32 d_z = pos_a.z - pos_b.z;
	return sqrtf(d_x*d_x + d_y * d_y + d_z * d_z);
}

Vec3 get_bone_by_id(i_entity* p_entity, int16 bone_id)
{
	i_character_instance* p_character = p_entity->get_character(0);
	if (!is_valid_ptr(p_character))
		return Vec3(type_zero::_zero);

	i_skeleteon_pose_id* p_skeleton_id = p_character->get_skeleteon_pose_id();
	if (!is_valid_ptr(p_skeleton_id))
		return Vec3(type_zero::_zero);

	Matrix34 m_out = p_entity->get_world_tm() * Matrix34(p_skeleton_id->get_abs_joint_by_id(bone_id));
	return m_out.get_translation();
}

Vec3 get_bone_by_name(i_entity* p_entity, c_char sz_joint_name)
{
	i_character_instance* p_character = p_entity->get_character(0);
	if (!is_valid_ptr(p_character))
		return Vec3(type_zero::_zero);

	i_skeleteon_pose* p_skeleton = p_character->get_skeleton_pose();
	if (!is_valid_ptr(p_skeleton))
		return Vec3(type_zero::_zero);

	int16 bone_id = p_skeleton->get_joint_id_by_name(sz_joint_name);
	if (bone_id == -1)
		return { type_zero::_zero };

	return get_bone_by_id(p_entity, bone_id);
}

void save_teleport_point()
{
	teleport_mg.sz_name_point = name_point;
	teleport_mg.v_point = m_pos;
	v_teleport.push_back(teleport_mg);
}

void teleport_to_point(i_entity* m_entity, int32 key_active_id)
{
	m_pos = m_entity->v_position;
	if (!v_teleport.empty())
	{
		if (key_manager_to_function(key_active_id))
		{
			if (point_selected == -1)
				m_entity->set_pos(v_teleport.front().v_point);
			else
				m_entity->set_pos(v_teleport[point_selected].v_point);
		}
	}
	return;
}

void teleport_to_enemy(i_entity* m_entity, i_entity* p_entity, Vec3 option_pos, int32 key_active_id, bool status)
{
	if (status == true)
	{
		Vec3 m_pos = { type_zero::_zero };
		Vec3 v_pos = p_entity->v_position;

		if (key_manager_to_function(key_active_id))
		{
			m_pos.x = v_pos.x + option_pos.x + 1.f;
			m_pos.y = v_pos.y + option_pos.y;
			m_pos.z = v_pos.z + option_pos.z;

			m_entity->set_pos(m_pos);
		}
	}
}

void magnet_enemy(i_entity* m_entity, i_entity* p_entity, Vec3 option_pos, int32 key_active_id, bool status)
{
	Vec3 v_pos = { type_zero::_zero };

	if (status == true && key_manager_to_function(key_active_id))
	{
		v_pos.x = m_entity->v_position.x + option_pos.x + 1.f;
		v_pos.y = m_entity->v_position.y + option_pos.y;
		v_pos.z = m_entity->v_position.z + option_pos.z;

		p_entity->set_pos(v_pos);
	}
}

void magnet_object(i_entity* m_entity, i_entity* p_entity, c_char object_name, c_char name, Vec3 option_pos, int32 key_active_id, bool status)
{
	Vec3 v_pos = { type_zero::_zero };

	if (status == true && strstr(object_name, name) && !p_entity->is_hidden() && key_manager_to_function(key_active_id))
	{
		v_pos = m_entity->v_position + option_pos;		
		p_entity->set_pos(v_pos);
	}
}

void teleport_to_object(i_entity* m_entity, i_entity* p_entity, c_char object_name, c_char name, Vec3 option_pos, int32 key_active_id, bool status)
{
	if (status == true)
	{
		Vec3 m_pos = { type_zero::_zero };

		if (strstr(object_name, name) && !p_entity->is_hidden() && key_manager_to_function(key_active_id))
		{
			Vec3 v_pos = p_entity->v_position;

			m_pos.x = v_pos.x + option_pos.x + 1.f;
			m_pos.y = v_pos.y + option_pos.y;
			m_pos.z = v_pos.z + option_pos.z;

			m_entity->set_pos(m_pos);
		}
	}
}

void set_scale(i_entity* m_entity, Vec3 v_scale, int32 key_active_id, bool status)
{
	Vec3 p_scale = { type_zero::_zero };

	if (status)
	{
		key_manager_to_function(key_active_id) ? p_scale = v_scale : p_scale = { 1.f, 1.f, 1.f };
		m_entity->set_scale(p_scale);
	}
}

void draw_bone(i_entity* p_entity, c_char s_bone, c_char e_bone, f32* color)
{
	Vec3 start_bone, end_bone;
	if (i_renderer::singleton()->world_to_screen(get_bone_by_name(p_entity, s_bone), &start_bone))
		if (i_renderer::singleton()->world_to_screen(get_bone_by_name(p_entity, e_bone), &end_bone))
			render_line(ImVec2(start_bone.x, start_bone.y), ImVec2(end_bone.x, end_bone.y), color);
}

void esp_skeleton(i_entity* p_entity, f32* color)
{
	draw_bone(p_entity, xor_a("Bip01 Head"), xor_a("Bip01 Neck"), color);
	draw_bone(p_entity, xor_a("Bip01 Head"), xor_a("Bip01 Neck"), color);
	draw_bone(p_entity, xor_a("Bip01 Neck"), xor_a("Bip01 R UpperArm"), color);
	draw_bone(p_entity, xor_a("Bip01 R UpperArm"), xor_a("Bip01 R ForeArm"), color);
	draw_bone(p_entity, xor_a("Bip01 R ForeArm"), xor_a("Bip01 R Hand"), color);
	draw_bone(p_entity, xor_a("Bip01 Neck"), xor_a("Bip01 L UpperArm"), color);
	draw_bone(p_entity, xor_a("Bip01 L UpperArm"), xor_a("Bip01 L ForeArm"), color);
	draw_bone(p_entity, xor_a("Bip01 L ForeArm"), xor_a("Bip01 L Hand"), color);
	draw_bone(p_entity, xor_a("Bip01 Neck"), xor_a("Bip01 Pelvis"), color);
	draw_bone(p_entity, xor_a("Bip01 Pelvis"), xor_a("Bip01 R Thigh"), color);
	draw_bone(p_entity, xor_a("Bip01 R Thigh"), xor_a("Bip01 R Calf"), color);
	draw_bone(p_entity, xor_a("Bip01 R Calf"), xor_a("Bip01 R Foot"), color);
	draw_bone(p_entity, xor_a("Bip01 Pelvis"), xor_a("Bip01 L Thigh"), color);
	draw_bone(p_entity, xor_a("Bip01 L Thigh"), xor_a("Bip01 L Calf"), color);
	draw_bone(p_entity, xor_a("Bip01 L Calf"), xor_a("Bip01 L Foot"), color);
}

void esp_2d_box(i_entity* p_entity, f32* color)
{
	Vec3 v_screen = { type_zero::_zero }, v_screen_end = { type_zero::_zero };
	if (i_renderer::singleton()->world_to_screen(get_bone_by_name(p_entity, xor_a("Bip01 Head")), &v_screen))
	{
		i_renderer::singleton()->world_to_screen(p_entity->v_position, &v_screen_end);
		f32 w = (v_screen_end.y - v_screen.y) / 4;
		render_border(v_screen.x - w, v_screen.y, w * 2, v_screen_end.y - v_screen.y, color);
	}
}

void esp_health(i_actor* p_actor, f32* color)
{
	Vec3 v_screen = { type_zero::_zero }, v_screen_end = { type_zero::_zero };
	if (i_renderer::singleton()->world_to_screen(get_bone_by_name(p_actor->get_entity(), xor_a("Bip01 Head")), &v_screen))
	{
		i_renderer::singleton()->world_to_screen(p_actor->get_entity()->v_position, &v_screen_end);
		f32 w = (v_screen_end.y - v_screen.y) / 4;
		f32 hw = (((v_screen_end.y - v_screen.y)*(p_actor->get_health())) / 100.f);
		render_box(v_screen.x + w + 2, v_screen.y, 4, hw, color);
		render_border(v_screen.x + w + 2, v_screen.y, 4, v_screen_end.y - v_screen.y, color);
	}
}

void esp_nick_name(i_entity* p_entity, f32* color)
{
	Vec3 v_screen = { type_zero::_zero };
	if (i_renderer::singleton()->world_to_screen(get_bone_by_name(p_entity, xor_a("Bip01")), &v_screen))
		render_text_default(ImVec2(v_screen.x, v_screen.y), to_cp1251(to_unicode(p_entity->get_name())), color);
}

void esp_rage_mode(i_actor* p_actor, i_entity* p_entity, const char* name, f32* color)
{
	Vec3 v_screen = { type_zero::_zero };
	if (i_renderer::singleton()->world_to_screen(get_bone_by_name(p_entity, xor_a("Bip01 Head")), &v_screen) && strstr(p_actor->get_current_item()->get_weapon_entity()->get_name(), xor_a("TerrorWeapon")))
		render_text_default(ImVec2(v_screen.x, v_screen.y - 13.f), name, color);
}

void esp_object_by_name(i_entity* p_entity, c_char object_name, c_char name, c_char caption, f32* color, bool status)
{
	if (status == true && strstr(object_name, name) && !p_entity->is_hidden())
	{
		Vec3 v_scr;
		Vec3 pos = p_entity->v_position;
		if (i_renderer::singleton()->world_to_screen(pos, &v_scr))
			render_text_default(ImVec2(v_scr.x, v_scr.y), caption, color);
	}
}

void esp_bone_ids(i_entity* p_entity, f32* color)
{
	int16 bone_ids;
	Vec3 v_bone, v_draw;

	for (bone_ids = 0; bone_ids < 151; bone_ids++)
	{
		v_bone = get_bone_by_id(p_entity, bone_ids);

		TCHAR buf[32];
		_itoa(bone_ids, buf, 10);

		if (i_renderer::singleton()->world_to_screen(v_bone, &v_draw))
			render_text_default(ImVec2(v_draw.x, v_draw.y), buf, color);
	}
}

void esp_objects_information(i_entity* m_entity, i_entity* p_entity, f32 dist, f32* color)
{
	Vec3 v_scr;
	Vec3 pos = p_entity->v_position;
	if (i_renderer::singleton()->world_to_screen(pos, &v_scr))
	{
		f32 calc_dist = calculate_distance(m_entity->v_position, p_entity->v_position);
		if (calc_dist < dist)
		{
			char _names[100];
			sprintf(_names, xor_a("%s"), p_entity->get_entity_class()->get_class_name());

			render_text_default(ImVec2(v_scr.x, v_scr.y), _names, color);
		}
	}
}

void calculate_rotation(Vec3 v_pos)
{
	f32 sqr = sqrt(v_pos.x*v_pos.x + v_pos.y*v_pos.y + v_pos.z*v_pos.z);
	v_pos.x = v_pos.x / sqr;
	v_pos.y = v_pos.y / sqr;
	v_pos.z = v_pos.z / sqr;
}

f32 get_hypotenuse(Vec3& vec_screen)
{
	f32 f_screen_center_x = (get_window_size().x * 0.5f);
	f32 f_screen_center_y = (get_window_size().y * 0.5f);

	f32 f_position_x = vec_screen.x > f_screen_center_x ? vec_screen.x - f_screen_center_x : f_screen_center_x - vec_screen.x;
	f32 f_position_y = vec_screen.y > f_screen_center_y ? vec_screen.y - f_screen_center_y : f_screen_center_y - vec_screen.y;
	return sqrt(f_position_x * f_position_x + f_position_y * f_position_y);
}

bool set_fov_aim(Vec3& p_vector, f32 size)
{
	f32 screen_center_x = (get_window_size().x * 0.5f);
	f32 screen_center_y = (get_window_size().y * 0.5f);

	return ((screen_center_x >= p_vector.x && screen_center_x <= p_vector.x + size / 2 && screen_center_y >= p_vector.y && screen_center_y <= p_vector.y + size / 2) ||
		sqrt((p_vector.x - screen_center_x) * (p_vector.x - screen_center_x) + (p_vector.y - screen_center_y) * (p_vector.y - screen_center_y)) <= size);
}

void set_vector_view(i_actor* m_actor, Vec3& p_hit_point)
{
	Vec3 v_pos = { type_zero::_zero };
	v_pos = p_hit_point - v_head;
	calculate_rotation(v_pos);
	m_actor->set_view_rotation(Quat::create_rotation_v_dir(v_pos.normalize()));
}