#pragma once

static void show_help_marker(const char* desc)
{
	ImGui::Text(xor_a("(?)"));
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

static void show_help_marker_to_text(const char* caption, const char* desc)
{
	ImGui::Text(caption);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void teleport_manager(bool opened)
{
	ImGui::SetNextWindowSize(ImVec2(490, 250), ImGuiSetCond_FirstUseEver);
	if (!ImGui::Begin(xor_a(u8"Manager Teleport"), &opened, ImGuiWindowFlags_NoCollapse))
	{
		ImGui::End();
		return;
	}

	ImGui::InputText(xor_a(u8"##tName"), name_point, 10); ImGui::SameLine();
	ImGui::Text(xor_a(u8"Vec3(%.2f,%.2f,%.2f)"), m_pos.x, m_pos.y, m_pos.z);
	if (ImGui::Button(xor_a(u8"Create point")))
		save_teleport_point();

	ImGui::Columns(2, xor_a("TeleportColumns"));
	ImGui::Separator();
	ImGui::Text(xor_a(u8"Name")); ImGui::NextColumn();
	ImGui::Text(xor_a(u8"Coordinate")); ImGui::NextColumn();
	ImGui::Separator();

	for (size_t i = 0; i < v_teleport.size(); i++)
	{
		if (ImGui::Selectable(v_teleport[i].sz_name_point.c_str(), point_selected == static_cast<int32_t>(i), ImGuiSelectableFlags_SpanAllColumns))
			point_selected = i;

		ImGui::NextColumn();
		ImGui::Text(xor_a(u8"Vec3(%.2f,%.2f,%.2f)"), v_teleport[i].v_point.x, v_teleport[i].v_point.y, v_teleport[i].v_point.z);
		ImGui::NextColumn();
	}

	ImGui::Columns(1);
	ImGui::Separator();

	if (ImGui::Button(xor_a(u8"Load all points")))
	{
		if (ifstream(xor_a(u8"teleportPoint.data")))
		{
			string out_s;
			ifstream oFile(xor_a(u8"teleportPoint.data"));
			while (true)
			{
				getline(oFile, out_s);
				if (!oFile.eof())
				{
					vector<string> Temp = split(out_s, '=');
					teleport_mg.sz_name_point = Temp[0];

					vector<string> vTemp = split(Temp[1].c_str(), ',');
					teleport_mg.v_point.z = strtof(vTemp[2].c_str(), 0);
					teleport_mg.v_point.y = strtof(vTemp[1].c_str(), 0);
					teleport_mg.v_point.x = strtof(vTemp[0].c_str(), 0);
					v_teleport.push_back(teleport_mg);
				}
				else
					break;
			}
		}
	}ImGui::SameLine();

	if (ImGui::Button(xor_a(u8"Save all points")))
	{
		ofstream oFile(xor_a(u8"teleportPoint.data"));
		for (size_t i = 0; i < v_teleport.size(); ++i)
		{
			oFile << v_teleport[i].sz_name_point << "=" <<
				v_teleport[i].v_point.x << "," <<
				v_teleport[i].v_point.y << "," <<
				v_teleport[i].v_point.z << "," <<
				endl;
		}
	}ImGui::SameLine();

	if (ImGui::Button(xor_a(u8"Clear all points")))
		v_teleport.clear();

	ImGui::End();
}

int iTab;
void styler()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 4.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.FramePadding = ImVec2(4, 2);
	style.FrameRounding = 0.0f;
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 16.0f;
	style.GrabMinSize = 0.1f;
	style.GrabRounding = 16.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.CurveTessellationTol = 1.25f;

	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.58f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.86f, 0.93f, 0.89f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.86f, 0.93f, 0.89f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.9f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
}

namespace Tabs
{
	void RenderVisuals()
	{
		static bool alpha_preview = true;
		static bool alpha_half_preview = false;
		static bool options_menu = true;
		static bool hdr = false;

		int misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
		ImGui::Checkbox(xor_a(u8"ESP Skeleteon"), &Settings::ESP::EspSkeleteon);
		ImGui::SameLine(300);
		ImGui::Checkbox(xor_a(u8"ESP 2D Box"), &Settings::ESP::Esp2dBox);
		ImGui::Checkbox(xor_a(u8"ESP Health"), &Settings::ESP::EspHelath);
		ImGui::SameLine(300);
		ImGui::Checkbox(xor_a(u8"ESP NickNames"), &Settings::ESP::EspNikname);
		ImGui::Checkbox(xor_a(u8"ESP Blood Bag"), &Settings::ESP::EspBloodBag);
		ImGui::SameLine(300);
		ImGui::Checkbox(xor_a(u8"ESP Ammo Loot"), &Settings::ESP::EspAmmo);
		ImGui::Checkbox(xor_a(u8"ESP Armor Loot"), &Settings::ESP::EspArmor);
		ImGui::SameLine(300);
		ImGui::Checkbox(xor_a(u8"ESP Health Loot"), &Settings::ESP::EspHealthBox);
		ImGui::Checkbox(xor_a(u8"ESP Fuse"), &Settings::ESP::EspFuse);
		ImGui::SameLine(300);
		ImGui::Checkbox(xor_a(u8"ESP Vampire Rage Mode"), &Settings::ESP::EspVampireRageMode);
		ImGui::PushItemWidth(150);
		ImGui::Separator();
		ImGui::ColorEdit4(xor_a("Skeleton##1"), (float*)&Settings::ESP::ColorSkeleton, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel | misc_flags);
		ImGui::SameLine(); ImGui::TextColored(ImColor(255.f, 255.f, 255.f, 255.f), xor_a("Skeleteon Color"));
		ImGui::SameLine(300);
		ImGui::ColorEdit4(xor_a("Boxes##1"), (float*)&Settings::ESP::Color2DBox, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel | misc_flags);
		ImGui::SameLine(); ImGui::TextColored(ImColor(255.f, 255.f, 255.f, 255.f), xor_a("2D Box Color"));
		ImGui::ColorEdit4(xor_a("Nicks##1"), (float*)&Settings::ESP::ColorNikname, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel | misc_flags);
		ImGui::SameLine(); ImGui::TextColored(ImColor(255.f, 255.f, 255.f, 255.f), xor_a("Nicks Color"));
		ImGui::SameLine(300);
		ImGui::ColorEdit4(xor_a("Health##1"), (float*)&Settings::ESP::ColorHelath, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel | misc_flags);
		ImGui::SameLine(); ImGui::TextColored(ImColor(255.f, 255.f, 255.f, 255.f), xor_a("Health Color"));
		ImGui::ColorEdit4(xor_a("RageVampire##1"), (float*)&Settings::ESP::ColorVampireRageMode, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel | misc_flags);
		ImGui::SameLine(); ImGui::TextColored(ImColor(255.f, 255.f, 255.f, 255.f), xor_a("Vampire Rage Mode Color"));
		ImGui::NextColumn();
	}

	void RenderAimbot()
	{
		ImGui::Checkbox(xor_a(u8"Enable Silent-Aim"), &Settings::Aimbot::Enabled);
		if (Settings::Aimbot::Enabled)
		{
			ImGui::Separator();
			ImGui::PushItemWidth(150);
			const char* szBone = xor_a(u8"Head \0Neck \0Spine \0Pelvis \0\0");
			ImGui::Combo(xor_a(u8"Target Bone"), &Settings::Aimbot::BoneSelect, szBone);
			ImGui::Checkbox(xor_a(u8"AutoShot"), &Settings::Aimbot::AutoShot);
			ImGui::Checkbox(xor_a(u8"WallShot"), &Settings::Aimbot::WallShot);
			ImGui::Separator();
			ImGui::Columns(2, "maincolum", false);
			ImGui::SetColumnOffset(1, 350);
			ImGui::Checkbox(xor_a(u8"Enable FOV"), &Settings::Aimbot::Fov::Enabled);

			if (Settings::Aimbot::Fov::Enabled)
				ImGui::SliderFloat(xor_a(u8"##4"), &Settings::Aimbot::Fov::Value, 0.f, 1000.f);
		}
	}

	void RenderMisc()
	{
		ImGui::PushItemWidth(200);
		ImGui::NextColumn();
		ImGui::Checkbox(xor_a(u8"NoRecoil"), &Settings::Function::NoRecoil);
		ImGui::SameLine(300);
		ImGui::Checkbox(xor_a(u8"NoSpread"), &Settings::Function::NoSpread);
		ImGui::Checkbox(xor_a(u8"NoClip [LSHIFT]"), &Settings::Function::NoClip);
		ImGui::SameLine(300);
		ImGui::SliderFloat(xor_a(u8"SpeedHack"), &Settings::Function::SpeedHack, 0.f, 10.f);
		ImGui::Checkbox(xor_a(u8"Unlimited Ammo"), &Settings::Function::UnlimAmmo);

		ImGui::Checkbox(xor_a("SetName"), &Settings::Function::SetName);

		if (Settings::Function::SetName)
			ImGui::InputText(xor_a("Input new name"), buff_name_set, sizeof(buff_name_set));
	}

	void RenderTeleport()
	{
		ImGui::PushItemWidth(200);
		ImGui::NextColumn();
		ImGui::Checkbox(xor_a("Teleport to point [B]"), &Settings::Teleport::tp_point);
		ImGui::Separator();
		if (Settings::Teleport::tp_point)
		{
			if (ImGui::Button(xor_a("Open Teleport Manager")))
				show_app_TeleportManager = !show_app_TeleportManager;

			ImGui::SameLine();
			if (Settings::Teleport::tp_point)
			{
				if (show_app_TeleportManager == true)
					teleport_manager(show_app_TeleportManager);
			}
		}

		ImGui::Checkbox(xor_a("Teleport to players [V]"), &Settings::Teleport::teleport_enemys::Enabled);
		if (Settings::Teleport::teleport_enemys::Enabled)
		{
			ImGui::SliderFloat(xor_a(u8"_X"), &Settings::Teleport::teleport_enemys::tp_x, 0.f, 20.f);
			ImGui::SliderFloat(xor_a(u8"_Y"), &Settings::Teleport::teleport_enemys::tp_y, 0.f, 20.f);
			ImGui::SliderFloat(xor_a(u8"_Z"), &Settings::Teleport::teleport_enemys::tp_z, 0.f, 20.f);
		}

		ImGui::Checkbox(xor_a("Magnet players [Z]"), &Settings::Teleport::mag_enemys::Enabled);
		if (Settings::Teleport::mag_enemys::Enabled)
		{
			ImGui::SliderFloat(xor_a(u8"_X"), &Settings::Teleport::mag_enemys::mg_x, 0.f, 20.f);
			ImGui::SliderFloat(xor_a(u8"_Y"), &Settings::Teleport::mag_enemys::mg_y, 0.f, 20.f);
			ImGui::SliderFloat(xor_a(u8"_Z"), &Settings::Teleport::mag_enemys::mg_z, 0.f, 20.f);
		}

		ImGui::Separator();
		ImGui::Checkbox(xor_a("Teleport to Blood Bag [Q]"), &Settings::Teleport::teleport_objects::tp_blood_bag);
		ImGui::Checkbox(xor_a("Teleport to Ammo Loot [Q]"), &Settings::Teleport::teleport_objects::tp_ammo);
		ImGui::Checkbox(xor_a("Teleport to Armor Loot [Q]"), &Settings::Teleport::teleport_objects::tp_armor);
		ImGui::Checkbox(xor_a("Teleport to Health Box [Q]"), &Settings::Teleport::teleport_objects::tp_health_box);
		ImGui::Checkbox(xor_a("Teleport to Fuse [Q]"), &Settings::Teleport::teleport_objects::tp_fuse);
	}

	void RenderOptions()
	{
		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(0, 100, 0);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(0, 190, 0);
		if (ImGui::Button(xor_a(u8"Save Functions")))
			create_cfg.save_settings();

		ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(100, 0, 0);
		ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] = ImColor(190, 0, 0);
		if (ImGui::Button(xor_a(u8"Reset Functions")))
			create_cfg.reset_settings();
	}
}

void im_menu()
{
	if (!show_menu)
		return;

	ImGuiStyle& style = ImGui::GetStyle();
	styler();
	static ImVec4 color = ImColor(18, 221, 233, 255);
	ImVec4* colors = style.Colors;

	static bool alpha_preview = true;
	static bool alpha_half_preview = false;
	static bool options_menu = true;
	static bool hdr = false;

	ImGui::SetNextWindowSize(ImVec2(900, 400));
	ImGui::Begin(xor_a("W1NNER PROJECT"), &show_menu, ImVec2(900, 400), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	{
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 230);
		style.ItemSpacing = ImVec2(0.f, 0.f);
		ImGui::BeginChild(xor_a("##tabs"), ImVec2(200, 360), false);
		{
			if (ImGui::Button(xor_a("ESP"), ImVec2(200, 45))) iTab = 0;
			if (ImGui::Button(xor_a("AIM"), ImVec2(200, 45))) iTab = 1;
			if (ImGui::Button(xor_a("MISC"), ImVec2(200, 45))) iTab = 2;
			if (ImGui::Button(xor_a("TELEPORT"), ImVec2(200, 45))) iTab = 3;
			if (ImGui::Button(xor_a("OPTIONS"), ImVec2(200, 45))) iTab = 4;
		}ImGui::EndChild();

		ImGui::NextColumn();

		styler();
		ImGui::BeginChild(xor_a("##main"), ImVec2(652, 360), true);
		{
			switch (iTab)
			{
			case 0:
				Tabs::RenderVisuals();
				break;
			case 1:
				Tabs::RenderAimbot();
				break;
			case 2:
				Tabs::RenderMisc();
				break;
			case 3:
				Tabs::RenderTeleport();
				break;
			case 4:
				Tabs::RenderOptions();
				break;
			}
		}ImGui::EndChild();
	}
	ImGui::End();
}

