#pragma once
#include <unordered_map>

char buff_name_set[1024];

class ColorVar
{
public:
	ImColor color;
	bool rainbow;
	float rainbowSpeed;

	ColorVar() {}

	ColorVar(ImColor color)
	{
		this->color = color;
		this->rainbow = false;
		this->rainbowSpeed = 0.5f;
	}

	ImColor Color()
	{
		ImColor result = this->color;
		result.Value.w = this->color.Value.w;
		return result;
	}
};

namespace Settings
{
	namespace Function
	{
		bool NoRecoil = false;
		bool NoSpread = false;
		bool NoClip = false;
		bool Overview = false;
		bool UnlimAmmo = false;
		bool SetName = false;
		float SpeedHack = 0.f;
	}

	namespace Aimbot
	{
		bool Enabled = false;
		bool AutoShot = false;
		bool WallShot = false;
		bool IsVisible = false;
		int BoneSelect = 0;

		namespace Fov
		{
			bool Enabled = false;
			float Value = 0.f;
		}
	}

	namespace ESP
	{
		bool EspSkeleteon = false;
		bool Esp2dBox = false;
		bool EspNikname = false;
		bool EspHelath = false;
		bool EspBloodBag = false;
		bool EspAmmo = false;
		bool EspArmor = false;
		bool EspHealthBox = false;
		bool EspFuse = false;
		bool EspVampireRageMode = false;

		ColorVar ColorSkeleton = ImColor(0.92f, 0.18f, 0.29f, 1.00f);
		ColorVar Color2DBox = ImColor(0.92f, 0.18f, 0.29f, 1.00f);
		ColorVar ColorNikname = ImColor(0.92f, 0.18f, 0.29f, 1.00f);
		ColorVar ColorHelath = ImColor(0.92f, 0.18f, 0.29f, 1.00f);
		ColorVar ColorVampireRageMode = ImColor(0.92f, 0.18f, 0.29f, 1.00f);
	}

	namespace Teleport
	{
		bool tp_point = false;

		namespace mag_enemys
		{
			bool Enabled = false;
			float mg_x = 0.f;
			float mg_y = 0.f;
			float mg_z = 0.f;
		}

		namespace teleport_enemys
		{
			bool Enabled = false;
			float tp_x = 0.f;
			float tp_y = 0.f;
			float tp_z = 0.f;
		}

		namespace teleport_objects
		{
			bool tp_blood_bag = false;
			bool tp_ammo = false;
			bool tp_health_box = false;
			bool tp_fuse = false;
			bool tp_armor = false;
		}
	}

	void load_defaults_or_save(std::string path);
	void load_config(std::string path);
}

void i_GetVal(Json::Value &config, int* setting)
{
	if (config.isNull())
		return;

	*setting = config.asInt();
}

void b_GetVal(Json::Value &config, bool* setting)
{
	if (config.isNull())
		return;

	*setting = config.asBool();
}

void f_GetVal(Json::Value &config, float* setting)
{
	if (config.isNull())
		return;

	*setting = config.asFloat();
}

void col_GetVal(Json::Value &config, ImColor* setting)
{
	if (config.isNull())
		return;

	f_GetVal(config[xor_a("r")], &setting->Value.x);
	f_GetVal(config[xor_a("g")], &setting->Value.y);
	f_GetVal(config[xor_a("b")], &setting->Value.z);
	f_GetVal(config[xor_a("a")], &setting->Value.w);
}

void s_GetVal(Json::Value &config, char** setting)
{
	if (config.isNull())
		return;

	*setting = _strdup(config.asCString());
}

void c_GetVal(Json::Value &config, char* setting)
{
	if (config.isNull())
		return;

	strcpy_s(setting, sizeof(setting), config.asCString());
}

void col_var_GetVal(Json::Value &config, ColorVar* setting)
{
	if (config.isNull())
		return;

	f_GetVal(config[xor_a("r")], &setting->color.Value.x);
	f_GetVal(config[xor_a("g")], &setting->color.Value.y);
	f_GetVal(config[xor_a("b")], &setting->color.Value.z);
	f_GetVal(config[xor_a("a")], &setting->color.Value.w);
	b_GetVal(config[xor_a("rainbow")], &setting->rainbow);
	f_GetVal(config[xor_a("rainbowSpeed")], &setting->rainbowSpeed);
}

template <typename Ord, Ord(*lookupFunction)(std::string)>
void GetOrdinal(Json::Value& config, Ord* setting)
{
	if (config.isNull())
		return;

	Ord value;
	if (config.isString())
		value = lookupFunction(config.asString());
	else
		value = (Ord)config.asInt();

	*setting = value;
}

void LoadColor(Json::Value &config, ImColor color)
{
	config[xor_a("r")] = color.Value.x;
	config[xor_a("g")] = color.Value.y;
	config[xor_a("b")] = color.Value.z;
	config[xor_a("a")] = color.Value.w;
}

void LoadColor(Json::Value &config, ColorVar color)
{
	config[xor_a("r")] = color.color.Value.x;
	config[xor_a("g")] = color.color.Value.y;
	config[xor_a("b")] = color.color.Value.z;
	config[xor_a("a")] = color.color.Value.w;
	config[xor_a("rainbow")] = color.rainbow;
	config[xor_a("rainbowSpeed")] = color.rainbowSpeed;
}

void Settings::load_defaults_or_save(std::string path)
{
	Json::Value settings;
	Json::StyledWriter styledWriter;

	//Function
	settings[xor_a("Function")][xor_a("NoRecoil")] = Settings::Function::NoRecoil;
	settings[xor_a("Function")][xor_a("NoSpread")] = Settings::Function::NoSpread;
	settings[xor_a("Function")][xor_a("NoClip")] = Settings::Function::NoClip;
	settings[xor_a("Function")][xor_a("Overview")] = Settings::Function::Overview;
	settings[xor_a("Function")][xor_a("UnlimAmmo")] = Settings::Function::UnlimAmmo;
	settings[xor_a("Function")][xor_a("SetName")] = Settings::Function::SetName;
	settings[xor_a("Function")][xor_a("buff_name_set")] = buff_name_set;
	settings[xor_a("Function")][xor_a("SpeedHack")] = Settings::Function::SpeedHack;

	//Aimbot
	settings[xor_a("Aimbot")][xor_a("Enabled")] = Settings::Aimbot::Enabled;
	settings[xor_a("Aimbot")][xor_a("AutoShot")] = Settings::Aimbot::AutoShot;
	settings[xor_a("Aimbot")][xor_a("WallShot")] = Settings::Aimbot::WallShot;
	settings[xor_a("Aimbot")][xor_a("IsVisible")] = Settings::Aimbot::IsVisible;
	settings[xor_a("Aimbot")][xor_a("BoneSelect")] = Settings::Aimbot::BoneSelect;
	settings[xor_a("Aimbot")][xor_a("Fov")][xor_a("Enabled")] = Settings::Aimbot::Fov::Enabled;
	settings[xor_a("Aimbot")][xor_a("Fov")][xor_a("Value")] = Settings::Aimbot::Fov::Value;

	//ESP
	settings[xor_a("ESP")][xor_a("EspSkeleteon")] = Settings::ESP::EspSkeleteon;
	settings[xor_a("ESP")][xor_a("Esp2dBox")] = Settings::ESP::Esp2dBox;
	settings[xor_a("ESP")][xor_a("EspNikname")] = Settings::ESP::EspNikname;
	settings[xor_a("ESP")][xor_a("EspHelath")] = Settings::ESP::EspHelath;
	settings[xor_a("ESP")][xor_a("EspBloodBag")] = Settings::ESP::EspBloodBag;
	settings[xor_a("ESP")][xor_a("EspAmmo")] = Settings::ESP::EspAmmo;
	settings[xor_a("ESP")][xor_a("EspArmor")] = Settings::ESP::EspArmor;
	settings[xor_a("ESP")][xor_a("EspHealthBox")] = Settings::ESP::EspHealthBox;
	settings[xor_a("ESP")][xor_a("EspFuse")] = Settings::ESP::EspFuse;
	settings[xor_a("ESP")][xor_a("EspVampireRageMode")] = Settings::ESP::EspVampireRageMode;

	LoadColor(settings[xor_a("ESP")][xor_a("ColorSkeleton")], Settings::ESP::ColorSkeleton);
	LoadColor(settings[xor_a("ESP")][xor_a("Color2Dboxx")], Settings::ESP::Color2DBox);
	LoadColor(settings[xor_a("ESP")][xor_a("ColorNikname")], Settings::ESP::ColorNikname);
	LoadColor(settings[xor_a("ESP")][xor_a("ColorHelath")], Settings::ESP::ColorHelath);
	LoadColor(settings[xor_a("ESP")][xor_a("ColorVampireRageMode")], Settings::ESP::ColorVampireRageMode);

	//Teleport
	settings[xor_a("Teleport")][xor_a("tp_point")] = Settings::Teleport::tp_point;
	settings[xor_a("Teleport")][xor_a("mag_enemys")][xor_a("Enabled")] = Settings::Teleport::mag_enemys::Enabled;
	settings[xor_a("Teleport")][xor_a("mag_enemys")][xor_a("x")] = Settings::Teleport::mag_enemys::mg_x;
	settings[xor_a("Teleport")][xor_a("mag_enemys")][xor_a("y")] = Settings::Teleport::mag_enemys::mg_y;
	settings[xor_a("Teleport")][xor_a("mag_enemys")][xor_a("z")] = Settings::Teleport::mag_enemys::mg_z;

	settings[xor_a("Teleport")][xor_a("teleport_enemys")][xor_a("Enabled")] = Settings::Teleport::teleport_enemys::Enabled;
	settings[xor_a("Teleport")][xor_a("teleport_enemys")][xor_a("x")] = Settings::Teleport::teleport_enemys::tp_x;
	settings[xor_a("Teleport")][xor_a("teleport_enemys")][xor_a("y")] = Settings::Teleport::teleport_enemys::tp_y;
	settings[xor_a("Teleport")][xor_a("teleport_enemys")][xor_a("z")] = Settings::Teleport::teleport_enemys::tp_z;

	settings[xor_a("Teleport")][xor_a("teleport_objects")][xor_a("tp_blood_bag")] = Settings::Teleport::teleport_objects::tp_blood_bag;
	settings[xor_a("Teleport")][xor_a("teleport_objects")][xor_a("tp_ammo")] = Settings::Teleport::teleport_objects::tp_ammo;
	settings[xor_a("Teleport")][xor_a("teleport_objects")][xor_a("tp_health_box")] = Settings::Teleport::teleport_objects::tp_health_box;
	settings[xor_a("Teleport")][xor_a("teleport_objects")][xor_a("tp_fuse")] = Settings::Teleport::teleport_objects::tp_fuse;
	settings[xor_a("Teleport")][xor_a("teleport_objects")][xor_a("tp_armor")] = Settings::Teleport::teleport_objects::tp_armor;

	std::ofstream(path) << styledWriter.write(settings);
}

void Settings::load_config(std::string path)
{
	if (!std::ifstream(path).good())
	{
		Settings::load_defaults_or_save(path);
		return;
	}

	Json::Value settings;
	std::ifstream configDoc(path, std::ifstream::binary);
	configDoc >> settings;

	//Function
	b_GetVal(settings[xor_a("Function")][xor_a("NoRecoil")], &Settings::Function::NoRecoil);
	b_GetVal(settings[xor_a("Function")][xor_a("NoSpread")], &Settings::Function::NoSpread);
	b_GetVal(settings[xor_a("Function")][xor_a("NoClip")], &Settings::Function::NoClip);
	b_GetVal(settings[xor_a("Function")][xor_a("Overview")], &Settings::Function::Overview);
	b_GetVal(settings[xor_a("Function")][xor_a("UnlimAmmo")], &Settings::Function::UnlimAmmo);
	b_GetVal(settings[xor_a("Function")][xor_a("SetName")], &Settings::Function::SetName);
	c_GetVal(settings[xor_a("Function")][xor_a("buff_name_set")], buff_name_set);
	f_GetVal(settings[xor_a("Function")][xor_a("SpeedHack")], &Settings::Function::SpeedHack);

	//Aimbot
	b_GetVal(settings[xor_a("Aimbot")][xor_a("Enabled")], &Settings::Aimbot::Enabled);
	b_GetVal(settings[xor_a("Aimbot")][xor_a("AutoShot")], &Settings::Aimbot::AutoShot);
	b_GetVal(settings[xor_a("Aimbot")][xor_a("WallShot")], &Settings::Aimbot::WallShot);
	b_GetVal(settings[xor_a("Aimbot")][xor_a("IsVisible")], &Settings::Aimbot::IsVisible);
	i_GetVal(settings[xor_a("Aimbot")][xor_a("BoneSelect")], &Settings::Aimbot::BoneSelect);
	b_GetVal(settings[xor_a("Aimbot")][xor_a("Fov")][xor_a("Enabled")], &Settings::Aimbot::Fov::Enabled);
	f_GetVal(settings[xor_a("Aimbot")][xor_a("Fov")][xor_a("Value")], &Settings::Aimbot::Fov::Value);

	//ESP
	b_GetVal(settings[xor_a("ESP")][xor_a("EspSkeleteon")], &Settings::ESP::EspSkeleteon);
	b_GetVal(settings[xor_a("ESP")][xor_a("Esp2dBox")], &Settings::ESP::Esp2dBox);
	b_GetVal(settings[xor_a("ESP")][xor_a("EspNikname")], &Settings::ESP::EspNikname);
	b_GetVal(settings[xor_a("ESP")][xor_a("EspHelath")], &Settings::ESP::EspHelath);
	b_GetVal(settings[xor_a("ESP")][xor_a("EspBloodBag")], &Settings::ESP::EspBloodBag);
	b_GetVal(settings[xor_a("ESP")][xor_a("EspAmmo")], &Settings::ESP::EspAmmo);
	b_GetVal(settings[xor_a("ESP")][xor_a("EspArmor")], &Settings::ESP::EspArmor);
	b_GetVal(settings[xor_a("ESP")][xor_a("EspHealthBox")], &Settings::ESP::EspHealthBox);
	b_GetVal(settings[xor_a("ESP")][xor_a("EspFuse")], &Settings::ESP::EspFuse);
	b_GetVal(settings[xor_a("ESP")][xor_a("EspVampireRageMode")], &Settings::ESP::EspVampireRageMode);

	col_var_GetVal(settings[xor_a("ESP")][xor_a("ColorSkeleton")], &Settings::ESP::ColorSkeleton);
	col_var_GetVal(settings[xor_a("ESP")][xor_a("Color2Dboxx")], &Settings::ESP::Color2DBox);
	col_var_GetVal(settings[xor_a("ESP")][xor_a("ColorNikname")], &Settings::ESP::ColorNikname);
	col_var_GetVal(settings[xor_a("ESP")][xor_a("ColorHelath")], &Settings::ESP::ColorHelath);
	col_var_GetVal(settings[xor_a("ESP")][xor_a("ColorVampireRageMode")], &Settings::ESP::ColorVampireRageMode);

	//Teleport
	b_GetVal(settings[xor_a("Teleport")][xor_a("tp_point")], &Settings::Teleport::tp_point);
	b_GetVal(settings[xor_a("Teleport")][xor_a("mag_enemys")][xor_a("Enabled")], &Settings::Teleport::mag_enemys::Enabled);
	f_GetVal(settings[xor_a("Teleport")][xor_a("mag_enemys")][xor_a("x")], &Settings::Teleport::mag_enemys::mg_x);
	f_GetVal(settings[xor_a("Teleport")][xor_a("mag_enemys")][xor_a("y")], &Settings::Teleport::mag_enemys::mg_y);
	f_GetVal(settings[xor_a("Teleport")][xor_a("mag_enemys")][xor_a("z")], &Settings::Teleport::mag_enemys::mg_z);
	b_GetVal(settings[xor_a("Teleport")][xor_a("teleport_enemys")][xor_a("Enabled")], &Settings::Teleport::teleport_enemys::Enabled);
	f_GetVal(settings[xor_a("Teleport")][xor_a("teleport_enemys")][xor_a("x")], &Settings::Teleport::teleport_enemys::tp_x);
	f_GetVal(settings[xor_a("Teleport")][xor_a("teleport_enemys")][xor_a("y")], &Settings::Teleport::teleport_enemys::tp_y);
	f_GetVal(settings[xor_a("Teleport")][xor_a("teleport_enemys")][xor_a("z")], &Settings::Teleport::teleport_enemys::tp_z);

	b_GetVal(settings[xor_a("Teleport")][xor_a("teleport_objects")][xor_a("tp_blood_bag")], &Settings::Teleport::teleport_objects::tp_blood_bag);
	b_GetVal(settings[xor_a("Teleport")][xor_a("teleport_objects")][xor_a("tp_ammo")], &Settings::Teleport::teleport_objects::tp_ammo);
	b_GetVal(settings[xor_a("Teleport")][xor_a("teleport_objects")][xor_a("tp_health_box")], &Settings::Teleport::teleport_objects::tp_health_box);
	b_GetVal(settings[xor_a("Teleport")][xor_a("teleport_objects")][xor_a("tp_fuse")], &Settings::Teleport::teleport_objects::tp_fuse);
	b_GetVal(settings[xor_a("Teleport")][xor_a("teleport_objects")][xor_a("tp_armor")], &Settings::Teleport::teleport_objects::tp_armor);
}

class cSettingsFile
{
public:
	cSettingsFile(char* szFileName)
	{
		memset(m_szFileName, 0x00, 255);
		memset(dlldir, 0x00, 320);
		memcpy_s(m_szFileName, sizeof m_szFileName, szFileName, strlen(szFileName));
		SHGetSpecialFolderPath(0, dlldir, CSIDL_APPDATA, true);
		sprintf_s(UEngineCfg, "%s\\%s", dlldir, szFileName);
	}

	void save_settings();
	void load_settings();
	void reset_settings()
	{
		Settings::Function::NoRecoil = false;
		Settings::Function::NoSpread = false;
		Settings::Function::NoClip = false;
		Settings::Function::Overview = false;
		Settings::Function::UnlimAmmo = false;
		Settings::Function::SetName = false;
		Settings::Function::SpeedHack = 0.f;

		Settings::Aimbot::Enabled = false;
		Settings::Aimbot::AutoShot = false;
		Settings::Aimbot::WallShot = false;
		Settings::Aimbot::IsVisible = false;
		Settings::Aimbot::BoneSelect = 0;
		Settings::Aimbot::Fov::Enabled = false;
		Settings::Aimbot::Fov::Value = 0.f;

		Settings::ESP::EspSkeleteon = false;
		Settings::ESP::Esp2dBox = false;
		Settings::ESP::EspNikname = false;
		Settings::ESP::EspHelath = false;
		Settings::ESP::EspBloodBag = false;
		Settings::ESP::EspAmmo = false;
		Settings::ESP::EspArmor = false;
		Settings::ESP::EspHealthBox = false;
		Settings::ESP::EspFuse = false;
		Settings::ESP::ColorSkeleton = ImColor(0.92f, 0.18f, 0.29f, 1.00f);
		Settings::ESP::Color2DBox = ImColor(0.92f, 0.18f, 0.29f, 1.00f);
		Settings::ESP::ColorNikname = ImColor(0.92f, 0.18f, 0.29f, 1.00f);
		Settings::ESP::ColorHelath = ImColor(0.92f, 0.18f, 0.29f, 1.00f);

		Settings::Teleport::tp_point = false;
		Settings::Teleport::teleport_enemys::Enabled = false;
		Settings::Teleport::teleport_enemys::tp_x = 0.f;
		Settings::Teleport::teleport_enemys::tp_y = 0.f;
		Settings::Teleport::teleport_enemys::tp_z = 0.f;

		Settings::Teleport::mag_enemys::Enabled = false;
		Settings::Teleport::mag_enemys::mg_x = 0.f;
		Settings::Teleport::mag_enemys::mg_y = 0.f;
		Settings::Teleport::mag_enemys::mg_z = 0.f;

		DeleteFile(UEngineCfg);
		load_settings();
	}

	TCHAR	 m_szFileName[255];
	TCHAR    dlldir[320];
	TCHAR    UEngineCfg[MAX_PATH];
};

#pragma warning(push)
#pragma warning(disable:4018)
void cSettingsFile::save_settings()
{
	MessageBeep(MB_ICONEXCLAMATION);
	Settings::load_defaults_or_save(UEngineCfg);
};

void cSettingsFile::load_settings()
{
	MessageBeep(MB_ICONEXCLAMATION);
	Settings::load_config(UEngineCfg);
};
#pragma warning (pop)

cSettingsFile create_cfg(xor_a("funcops.cfg"));