#pragma once
#include "Protocol.pb.h"

enum PlayerType
{
	PLAYER_TYPE_NONE = 0, 
	PLAYER_TYPE_KNIGHT = 1,
	PLAYER_TYPE_MAGE = 2,
	PLAYER_TYPE_ARCHER = 3,
};

class CharacterInfo
{
public:
	CharacterInfo() = default;
	CharacterInfo(Protocol::CharacterInfo* characterInfo);

public:
	uint64 characterId;
	PlayerType playerType;
	string name;
	uint32 level;
	int32 hp;
	int32 exp;
	uint32 attack;
	uint32 mapId;
};

