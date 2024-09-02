#pragma once
#include "CharacterInfo.h"

enum BaseState
{
	IDLE = 0,
	MOVING = 1,
	SKILL = 2,
	DEAD = 3,
	JUMP = 4,
};

enum MoveDir
{
	LEFT = 0,
	RIGHT = 1,
};

struct CreatureState 
{
	float posX = 0.0;
	float posY = 0.0;
	BaseState baseState = IDLE;
	MoveDir moveDir = LEFT;
};

class Player
{
public:
	Player() = default;
	uint64 playerId = 0;
	uint64 characterId = 0;
	PlayerType playerType;
	string name;
	CreatureState playerState;

	GameSessionRef ownerSession;
};