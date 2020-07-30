#pragma once
#include "cry_reversing_tools.h"

void create_circle_fov()
{
	if (Settings::Aimbot::Fov::Enabled == true)
		render_circle(ImVec2(get_window_size().x * 0.5f, get_window_size().y * 0.5f), Settings::Aimbot::Fov::Value, (f32*)&ImColor(238, 6, 25, 255), 1.f);
}

void create_function(i_item_system* m_item_system, i_entity* m_entity, i_weapon* m_weapon, i_actor* m_actor)
{
	m_head = get_bone_by_name(m_entity, xor_a("Bip01 Neck"));

	if (Settings::Teleport::tp_point == true)
		teleport_to_point(m_entity, VK_B);

	if (Settings::Function::SetName)
		m_entity->set_name(buff_name_set);

	if (!strstr(weapon_name, xor_a("DeceitKnife")) && !strstr(weapon_name, xor_a("TerrorWeapon")))
	{
		if (Settings::Function::UnlimAmmo)
			m_weapon->m_ammo->count = 9999;

		if (Settings::Function::NoRecoil)
		{
			s_recoil_mod_params recoil_params;
			m_weapon->m_fm->set_recoil_param(&recoil_params, 1.f);
		}
		
		if (Settings::Function::NoSpread)
		{
			m_weapon->m_fm->fl_max_spread = 0.f;
			m_weapon->m_fm->fl_min_spread = 0.f;
		}
	}

	m_actor->set_actor_function(0x180, 4.f + Settings::Function::SpeedHack);
	set_scale(m_entity, Vec3(100.f, 100.f, 1.f), VK_LSHIFT, Settings::Function::NoClip);
}

void create_actors(i_entity* m_entity, i_actor* m_actor, i_weapon* m_weapon, i_actor_system* m_actor_system)
{
	f32 max_dist = 1000.f;
	f32 min_dist = 0.f;
	Vec3 v_out = { type_zero::_zero };

	target.bone_hit_point = { type_zero::_zero };
	target.p_result = 0;

	i_actor_iterator* p_actor_iterator = nullptr;
	m_actor_system->create_actor_iterator(&p_actor_iterator);
	while (i_actor* p_actor = p_actor_iterator->actor_next())
	{
		if (!elimination_actor(m_actor, p_actor))
			continue;

		if (i_entity* p_actor_entity = p_actor->get_entity())
		{
			//////////////////////////////////
			v_head = get_bone_by_name(p_actor_entity, xor_a("Bip01 Neck"));
			//////////////////////////////////

			//////////////////////////////////
			magnet_enemy(m_entity, p_actor_entity, Vec3(Settings::Teleport::mag_enemys::mg_x, Settings::Teleport::mag_enemys::mg_y, Settings::Teleport::mag_enemys::mg_z), VK_Z, Settings::Teleport::mag_enemys::Enabled);
			teleport_to_enemy(m_entity, p_actor_entity, Vec3(Settings::Teleport::teleport_enemys::tp_x, Settings::Teleport::teleport_enemys::tp_y, Settings::Teleport::teleport_enemys::tp_z), VK_V, Settings::Teleport::teleport_enemys::Enabled);
			//////////////////////////////////

			//////////////////////////////////
			if (p_actor->is_dead())
				continue;
			if (!i_renderer::singleton()->world_to_screen(v_head, &v_out))
				continue;
			if (Settings::Aimbot::Fov::Enabled == true && !set_fov_aim(v_out, Settings::Aimbot::Fov::Value))
				continue;
			//////////////////////////////////

            //////////////////////////////////
			Vec3 vec_aim_bone = v_head;
			min_dist = get_hypotenuse(v_out);
			if (min_dist <= max_dist)
			{
				target.p_result = p_actor->get_entity_id();
				target.bone_hit_point = vec_aim_bone;
				max_dist = min_dist;
			}

			if (target.p_result != 0)
				start_shots(m_weapon, Settings::Aimbot::AutoShot);
			//////////////////////////////////
		}
	}
}

void create_entites(i_entity* m_entity, i_actor* m_actor, i_entity_system* m_entity_system)
{
	i_entity_it* p_entity_iterator = nullptr;
	m_entity_system->create_entity_iterator(&p_entity_iterator);
	p_entity_iterator->move_first();

	while (i_entity* p_entity = p_entity_iterator->entity_next())
	{
		teleport_to_object(m_entity, p_entity, p_entity->get_entity_class()->get_class_name(), xor_a("BloodBagConsumable"), type_zero::_zero, VK_Q, Settings::Teleport::teleport_objects::tp_blood_bag);
		teleport_to_object(m_entity, p_entity, p_entity->get_entity_class()->get_class_name(), xor_a("HealthConsumable"), type_zero::_zero, VK_Q, Settings::Teleport::teleport_objects::tp_health_box);
		teleport_to_object(m_entity, p_entity, p_entity->get_entity_class()->get_class_name(), xor_a("AmmoConsumable"), type_zero::_zero, VK_Q, Settings::Teleport::teleport_objects::tp_ammo);
		teleport_to_object(m_entity, p_entity, p_entity->get_entity_class()->get_class_name(), xor_a("ArmourConsumable"), type_zero::_zero, VK_Q, Settings::Teleport::teleport_objects::tp_armor);
		teleport_to_object(m_entity, p_entity, p_entity->get_entity_class()->get_class_name(), xor_a("FuseConsumable"), type_zero::_zero, VK_Q, Settings::Teleport::teleport_objects::tp_fuse);
	}

	if (p_entity_iterator)
		p_entity_iterator->release();
}

void create_esp_actors(i_entity* m_entity, i_actor* m_actor, i_actor_system* m_actor_system)
{
	i_actor_iterator* p_actor_iterator = nullptr;
	m_actor_system->create_actor_iterator(&p_actor_iterator);
	while (i_actor* p_actor = p_actor_iterator->actor_next())
	{
		if (!elimination_actor(m_actor, p_actor))
			continue;

		if (i_entity* p_entity = p_actor->get_entity())
		{
			if (Settings::ESP::EspSkeleteon)
				esp_skeleton(p_entity, (f32*)&Settings::ESP::ColorSkeleton);

			if (Settings::ESP::Esp2dBox)
				esp_2d_box(p_entity, (f32*)&Settings::ESP::Color2DBox);

			if (Settings::ESP::EspNikname)
				esp_nick_name(p_entity, (f32*)&Settings::ESP::ColorNikname);

			if (Settings::ESP::EspHelath)
				esp_health(p_actor, (f32*)&Settings::ESP::ColorHelath);

			if (Settings::ESP::EspVampireRageMode)
				esp_rage_mode(p_actor, p_entity, xor_a("Vampire RAGE MODE"), (f32*)&Settings::ESP::ColorVampireRageMode);
		}
	}
}

void create_esp_entites(i_entity* m_entity, i_actor* m_actor, i_entity_system* m_entity_system)
{
	i_entity_it* p_entity_iterator = nullptr;
	m_entity_system->create_entity_iterator(&p_entity_iterator);
	p_entity_iterator->move_first();

	while (i_entity* p_entity = p_entity_iterator->entity_next())
	{
		esp_object_by_name(p_entity, p_entity->get_entity_class()->get_class_name(), xor_a("BloodBagConsumable"), xor_a("BLOOD BAG"), (f32*)&ImColor(255.f, 0.f, 0.f), Settings::ESP::EspBloodBag);
		esp_object_by_name(p_entity, p_entity->get_entity_class()->get_class_name(), xor_a("HealthConsumable"), xor_a("HEALTH"), (f32*)&ImColor(0.f, 255.f, 0.f), Settings::ESP::EspHealthBox);
		esp_object_by_name(p_entity, p_entity->get_entity_class()->get_class_name(), xor_a("AmmoConsumable"), xor_a("AMMO"), (f32*)&ImColor(255.f, 165.f, 0.f), Settings::ESP::EspAmmo);
		esp_object_by_name(p_entity, p_entity->get_entity_class()->get_class_name(), xor_a("ArmourConsumable"), xor_a("ARMOR"), (f32*)&ImColor(30.f, 144.f, 255.f), Settings::ESP::EspArmor);
		esp_object_by_name(p_entity, p_entity->get_entity_class()->get_class_name(), xor_a("FuseConsumable"), xor_a("FUSE"), (f32*)&ImColor(238.f, 201.f, 0.f), Settings::ESP::EspFuse);
	}

	if (p_entity_iterator)
		p_entity_iterator->release();
}

void create_present_engine()
{
	i_renderer* m_render = i_renderer::singleton();
	if (!is_valid_ptr(m_render))
		return;

	i_game_frame_work* m_game_framework = i_game_frame_work::singleton();
	if (!is_valid_ptr(m_game_framework))
		return;

	i_entity_system* m_entity_system = i_entity_system::singleton();
	if (!is_valid_ptr(m_entity_system))
		return;

	i_console* m_console = i_console::singleton();
	if (!is_valid_ptr(m_console))
		return;

	i_actor_system* m_actor_system = m_game_framework->get_actor_system();
	if (!is_valid_ptr(m_actor_system))
		return;

	i_item_system* m_item_system = m_game_framework->get_item_system();
	if (!is_valid_ptr(m_item_system))
		return;

	i_actor* m_actor = m_game_framework->get_client_actor();
	if (!is_valid_ptr(m_actor))
		return;

	i_entity* m_entity = m_game_framework->get_client_entity();
	if (!is_valid_ptr(m_entity))
		return;

	i_item* m_current_item = m_actor->get_current_item();
	if (!is_valid_ptr(m_current_item))
		return;

	i_weapon* m_weapon = m_current_item->get_weapon();
	if (!is_valid_ptr(m_weapon))
		return;

	create_esp_actors(m_entity, m_actor, m_actor_system);
	create_esp_entites(m_entity, m_actor, m_entity_system);
}

void create_frame_engine()
{
	i_renderer* m_render = i_renderer::singleton();
	if (!is_valid_ptr(m_render))
		return;

	i_game_frame_work* m_game_framework = i_game_frame_work::singleton();
	if (!is_valid_ptr(m_game_framework))
		return;

	i_entity_system* m_entity_system = i_entity_system::singleton();
	if (!is_valid_ptr(m_entity_system))
		return;

	i_console* m_console = i_console::singleton();
	if (!is_valid_ptr(m_console))
		return;

	i_actor_system* m_actor_system = m_game_framework->get_actor_system();
	if (!is_valid_ptr(m_actor_system))
		return;

	i_item_system* m_item_system = m_game_framework->get_item_system();
	if (!is_valid_ptr(m_item_system))
		return;

	i_actor* m_actor = m_game_framework->get_client_actor();
	if (!is_valid_ptr(m_actor))
		return;

	i_entity* m_entity = m_game_framework->get_client_entity();
	if (!is_valid_ptr(m_entity))
		return;

	i_item* m_current_item = m_actor->get_current_item();
	if (!is_valid_ptr(m_current_item))
		return;

	i_weapon* m_weapon = m_current_item->get_weapon();
	if (!is_valid_ptr(m_weapon))
		return;

	weapon_name = m_current_item->get_weapon_entity()->get_name();
	create_function(m_item_system, m_entity, m_weapon, m_actor);
	create_actors(m_entity, m_actor, m_weapon, m_actor_system);
	create_entites(m_entity, m_actor, m_entity_system);
}


