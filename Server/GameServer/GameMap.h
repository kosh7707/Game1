#pragma once
#include "JobQueue.h"
#include "Player.h"

class GameMap : public JobQueue
{
public:
	void Enter(PlayerRef player);
	void Leave(PlayerRef player);
	void Broadcast(SendBufferRef sendBuffer);
	void HandleMoveStart(uint64 playerId, Protocol::C_MOVE_START pkt);
	void HandleMoveEnd(uint64 playerId, Protocol::C_MOVE_END pkt);
	void HandleJump(uint64 playerId, Protocol::C_JUMP pkt);
	void HandleJumpEnd(uint64 playerId, Protocol::C_JUMP_END pkt);
	void HandleSkill(uint64 playerId, Protocol::C_SKILL pkt);
	map<uint64, PlayerRef> GetPlayers();

private:
	USE_LOCK;
	map<uint64, PlayerRef> _players;
};

extern shared_ptr<GameMap> GGameMap;
