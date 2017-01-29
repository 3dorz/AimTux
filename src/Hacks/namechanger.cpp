#include "namechanger.h"

char* NameChanger::origName = strdup("");
int NameChanger::changes = -1;
NC_Type NameChanger::type = NC_NORMAL;

enum Colors
{
	WHITE = 1,
	DARK_RED,
	LIGHT_PURPLE,
	DARK_GREEN,
	LIGHT_GREEN,
	GREEN,
	LIGHT_RED,
	GRAY,
	YELLOW,
	LIGHT_BLUE,
	BLUE,
	DARK_BLUE,
	DARK_GRAY,
	PURPLE,
	RED,
	ORANGE,
};

char* NameChanger::GetName()
{
	IEngineClient::player_info_t playerInfo;
	engine->GetPlayerInfo(engine->GetLocalPlayer(), &playerInfo);
	char* buff;
	asprintf(&buff, "%s", playerInfo.name);
	return buff;
}

const char* Rainbowify(char* name)
{
	std::string base = " \x01\x0B";
	std::vector<char> rainbow = {
			(char)(Colors::RED),
			(char)(Colors::ORANGE),
			(char)(Colors::YELLOW),
			(char)(Colors::GREEN),
			(char)(Colors::BLUE),
			(char)(Colors::PURPLE),
	};

	unsigned int color = 0;
	for (char* it = name; *it; it++)
	{
		if (color > rainbow.size() - 1)
			color = 0;
		base.push_back(rainbow[color]);
		base.push_back(*it);
		color++;
	}

	base.append("\230");
	return base.c_str();
}

const char* Colorize(char* name, int color = Colors::LIGHT_RED)
{
	// TODO: Add color customization
	std::string res = " \x01\x0B";
	res += (char)(color);
	res.append(name);
	res.append("\230");
	return res.c_str();
}

void NameChanger::BeginFrame(float frameTime)
{
	if (!engine->IsInGame())
		return;

	if (changes == -1)
		return;

	long currentTime_ms = Util::GetEpochTime();
	static long timeStamp = currentTime_ms;

	if (currentTime_ms - timeStamp < 150)
		return;

	timeStamp = currentTime_ms;
	changes++;

	if (changes >= 5)
	{
		switch (NameChanger::type)
		{
			case NC_NORMAL:
				SetName(Util::PadStringRight("\nimm0rtal.xyz", strlen("\nimm0rtal.xyz") + RandomInt(10, 50)));
				break;
			case NC_RAINBOW:
<<<<<<< HEAD
				SetName(Util::PadStringRight(" \x01\x0B\x07""A""\x08""I""\x09""M""\x0A""T""\x0B""U""\x0C""X""\x0D"".""\x0E""N""\x0F""E""\x10""T\n", strlen(" \x01\x0B\x07""A""\x08""I""\x09""M""\x0A""T""\x0B""U""\x0C""X""\x0D"".""\x0E""N""\x0F""E""\x10""T\n") + RandomInt(10, 50)));
				break;
			case NC_SOLID:
				SetName(Util::PadStringRight(" \x01\x0B\x07""imm0rtal.xyz\n", strlen(" \x01\x0B\x07""imm0rtal.xyz\n") + RandomInt(10, 50)));
=======
				SetName(Util::PadStringRight(Rainbowify(origName), strlen(origName) + RandomInt(10, 50)));
				break;
			case NC_SOLID:
				SetName(Util::PadStringRight(Colorize(origName), strlen(origName) + RandomInt(10, 50)));
>>>>>>> refs/remotes/AimTuxOfficial/master
				break;
		}

		changes = -1;

		return;
	}

	SetName(Util::PadStringRight("imm0rtal.xyz", strlen("imm0rtal.xyz") + changes));
}

void NameChanger::SetName(const char* name)
{
	ConVar* cvar_name = cvar->FindVar("name");
	*(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
	cvar_name->SetValue(name);
}
