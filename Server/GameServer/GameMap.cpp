#include "pch.h"
#include "GameMap.h"
#include "GameSession.h"
#include "ClientPacketHandler.h"

shared_ptr<GameMap> GGameMap = make_shared<GameMap>();

void GameMap::Enter(PlayerRef player)
{
	WRITE_LOCK;
	_players[player->playerId] = player;
}

void GameMap::Leave(PlayerRef player)
{
	WRITE_LOCK;
	_players.erase(player->playerId);
}

void GameMap::Broadcast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for (auto& p : _players)
	{
		p.second->ownerSession->Send(sendBuffer);
	}
}

void GameMap::HandleMoveStart(uint64 playerId, Protocol::C_MOVE_START pkt)
{
	PlayerRef player = _players[playerId];

	// 유효성 검증 필요
	player->playerState.posX = pkt.state().posx();
	player->playerState.posY = pkt.state().posy();
	player->playerState.baseState = BaseState::MOVING;
	player->playerState.moveDir = (MoveDir)pkt.state().movedir();

	cout << "[Player_" << player->playerId << "] MoveStart ("
		<< player->playerState.posX << ","
		<< player->playerState.posY << ")" << endl;

	Protocol::CreatureState* creatureState = new Protocol::CreatureState();
	creatureState->set_posx(player->playerState.posX);
	creatureState->set_posy(player->playerState.posY);
	creatureState->set_basestate((Protocol::BaseState)player->playerState.baseState);
	creatureState->set_movedir((Protocol::MoveDir)player->playerState.moveDir);

	Protocol::S_MOVE_START moveStartPkt;
	moveStartPkt.set_playerid(player->playerId);
	moveStartPkt.set_allocated_state(creatureState);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(moveStartPkt);
	for (auto& p : _players) 
	{
		p.second->ownerSession->Send(sendBuffer);
	}
}

void GameMap::HandleMoveEnd(uint64 playerId, Protocol::C_MOVE_END pkt)
{
	PlayerRef player = _players[playerId];

	// 유효성 검증 필요
	player->playerState.posX = pkt.state().posx();
	player->playerState.posY = pkt.state().posy();
	player->playerState.baseState = BaseState::IDLE;
	player->playerState.moveDir = (MoveDir)pkt.state().movedir();

	cout << "[Player_" << player->playerId << "] MoveEnd ("
		<< player->playerState.posX << ","
		<< player->playerState.posY << ")" << endl;

	Protocol::CreatureState* creatureState = new Protocol::CreatureState();
	creatureState->set_posx(player->playerState.posX);
	creatureState->set_posy(player->playerState.posY);
	creatureState->set_basestate((Protocol::BaseState)player->playerState.baseState);
	creatureState->set_movedir((Protocol::MoveDir)player->playerState.moveDir);

	Protocol::S_MOVE_END moveEndPkt;
	moveEndPkt.set_playerid(player->playerId);
	moveEndPkt.set_allocated_state(creatureState);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(moveEndPkt);
	for (auto& p : _players)
	{
		p.second->ownerSession->Send(sendBuffer);
	}
}

void GameMap::HandleJump(uint64 playerId, Protocol::C_JUMP pkt)
{
	PlayerRef player = _players[playerId];

	// 유효성 검증 필요
	player->playerState.posX = pkt.state().posx();
	player->playerState.posY = pkt.state().posy();
	player->playerState.moveDir = (MoveDir)pkt.state().movedir();

	if (player->playerState.baseState != BaseState::IDLE 
			&& player->playerState.baseState != BaseState::MOVING)
	{
		cout << "[Player_" << player->playerId << "] Jump Failed ("
			<< player->playerState.posX << ","
			<< player->playerState.posY << ")" << endl;

		Protocol::S_JUMP jumpPkt;
		jumpPkt.set_success(false);
		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(jumpPkt);
		player->ownerSession->Send(sendBuffer);
	}
	else
	{
		cout << "[Player_" << player->playerId << "] Jump ("
			<< player->playerState.posX << ","
			<< player->playerState.posY << ")" << endl;

		player->playerState.baseState = BaseState::JUMP;

		Protocol::CreatureState* creatureState = new Protocol::CreatureState();
		creatureState->set_posx(player->playerState.posX);
		creatureState->set_posy(player->playerState.posY);
		creatureState->set_basestate((Protocol::BaseState)player->playerState.baseState);
		creatureState->set_movedir((Protocol::MoveDir)player->playerState.moveDir);
		
		Protocol::S_JUMP jumpPkt;
		jumpPkt.set_success(true);
		jumpPkt.set_playerid(player->playerId);
		jumpPkt.set_allocated_state(creatureState);

		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(jumpPkt);
		for (auto& p : _players)
		{
			p.second->ownerSession->Send(sendBuffer);
		}
	}
}

void GameMap::HandleJumpEnd(uint64 playerId, Protocol::C_JUMP_END pkt)
{
	PlayerRef player = _players[playerId];

	// 유효성 검증 필요
	player->playerState.posX = pkt.state().posx();
	player->playerState.posY = pkt.state().posy();
	player->playerState.baseState = BaseState::IDLE;
	player->playerState.moveDir = (MoveDir)pkt.state().movedir();

	cout << "[Player_" << player->playerId << "] JumpEnd ("
		<< player->playerState.posX << ","
		<< player->playerState.posY << ")" << endl;

	Protocol::CreatureState* creatureState = new Protocol::CreatureState();
	creatureState->set_posx(player->playerState.posX);
	creatureState->set_posy(player->playerState.posY);
	creatureState->set_basestate((Protocol::BaseState)player->playerState.baseState);
	creatureState->set_movedir((Protocol::MoveDir)player->playerState.moveDir);

	Protocol::S_JUMP_END jumpEndPkt;
	jumpEndPkt.set_playerid(player->playerId);
	jumpEndPkt.set_allocated_state(creatureState);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(jumpEndPkt);
	for (auto& p : _players)
	{
		p.second->ownerSession->Send(sendBuffer);
	}
	
}

void GameMap::HandleSkill(uint64 playerId, Protocol::C_SKILL pkt)
{
	PlayerRef player = _players[playerId];

	if (player->playerState.baseState == BaseState::IDLE ||
			player->playerState.baseState == BaseState::MOVING)
	{
		// 유효성 검증 필요
		player->playerState.posX = pkt.state().posx();
		player->playerState.posY = pkt.state().posy();
		player->playerState.baseState = BaseState::SKILL;
		player->playerState.moveDir = (MoveDir)pkt.state().movedir();

		cout << "[Player_" << player->playerId << "] UseSkill Success ("
			<< player->playerState.posX << ","
			<< player->playerState.posY << ")" << endl;

		Protocol::CreatureState* creatureState = new Protocol::CreatureState();
		creatureState->set_posx(player->playerState.posX);
		creatureState->set_posy(player->playerState.posY);
		creatureState->set_basestate((Protocol::BaseState)player->playerState.baseState);
		creatureState->set_movedir((Protocol::MoveDir)player->playerState.moveDir);

		Protocol::S_SKILL skillPkt;
		skillPkt.set_success(true);
		skillPkt.set_playerid(player->playerId);
		skillPkt.set_allocated_state(creatureState);

		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(skillPkt);
		for (auto& p : _players)
		{
			p.second->ownerSession->Send(sendBuffer);
		}
	}
	else
	{
		cout << "[Player_" << player->playerId << "] UseSkill Failed ("
			<< player->playerState.posX << ","
			<< player->playerState.posY << ")" << endl;

		Protocol::S_SKILL skillPkt;
		skillPkt.set_success(false);
		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(skillPkt);
		player->ownerSession->Send(sendBuffer);
	}
}

map<uint64, PlayerRef> GameMap::GetPlayers()
{
	return _players;
}
