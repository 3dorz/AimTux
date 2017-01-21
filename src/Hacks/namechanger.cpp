#include "namechanger.h"

int NameChanger::changes = -1;
NC_Type NameChanger::type = NC_NORMAL;

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
		/*
			\x01 WHITE
			\x02 DARK RED
			\x03 LIGHT PURPLE
			\x04 DARK GREEN
			\x05 LIGHT GREEN
			\x06 GREEN
			\x07 LIGHT RED
			\x08 GRAY
			\x09 YELLOW
			\x0A LIGHT BLUE
			\x0B BLUE
			\x0C DARK BLUE
			\x0D GRAY
			\x0E PURPLE
			\x0F RED
			\x10 ORANGE
		*/

		switch (NameChanger::type)
		{
			case NC_NORMAL:
				SetName(Util::PadStringRight("\nimm0rtal.xyz", strlen("\nimm0rtal.xyz") + RandomInt(10, 50)));
				break;
			case NC_RAINBOW:
				SetName(Util::PadStringRight(" \x01\x0B\x07""A""\x08""I""\x09""M""\x0A""T""\x0B""U""\x0C""X""\x0D"".""\x0E""N""\x0F""E""\x10""T\n", strlen(" \x01\x0B\x07""A""\x08""I""\x09""M""\x0A""T""\x0B""U""\x0C""X""\x0D"".""\x0E""N""\x0F""E""\x10""T\n") + RandomInt(10, 50)));
				break;
			case NC_SOLID:
				SetName(Util::PadStringRight(" \x01\x0B\x07""imm0rtal.xyz\n", strlen(" \x01\x0B\x07""imm0rtal.xyz\n") + RandomInt(10, 50)));
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
