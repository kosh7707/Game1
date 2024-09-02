#include "pch.h"
#include "ClientPacketHandler.h"
#include "GameSession.h"
#include "GameMap.h"
#include "GameSessionManager.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	return false;
}

bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt)
{
	std::cout << "[Client]: " << pkt.msg() << endl;

	Protocol::S_CHAT chatPkt;
	chatPkt.set_msg("Hello, Client!");
	SendBufferRef sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);
	
	session->Send(sendBuffer);

	return true;
}

bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	string id = pkt.id();
	string pw = pkt.pw();

	Protocol::S_LOGIN loginPkt;
	loginPkt.set_success(true);
	
	static Atomic<uint64> characterIdGenerator = 1;

	{
		Protocol::CharacterInfo* character = loginPkt.add_chracters();
		character->set_characterid(characterIdGenerator);
		character->set_playertype(Protocol::PLAYER_TYPE_KNIGHT);
		character->set_name("Kosh");
		character->set_level(1);
		character->set_hp(100);
		character->set_exp(0);
		character->set_attack(15);
		character->set_mapid(1);

		CharacterInfoRef characterInfoRef = MakeShared<CharacterInfo>(character);

		gameSession->characters.insert({ characterIdGenerator, characterInfoRef });
		characterIdGenerator++;
	}

	{
		Protocol::CharacterInfo* character = loginPkt.add_chracters();
		character->set_characterid(characterIdGenerator);
		character->set_playertype(Protocol::PLAYER_TYPE_ARCHER);
		character->set_name("LabSlave");
		character->set_level(1);
		character->set_hp(100);
		character->set_exp(0);
		character->set_attack(10);
		character->set_mapid(1);

		CharacterInfoRef characterInfoRef = MakeShared<CharacterInfo>(character);

		gameSession->characters.insert({ characterIdGenerator, characterInfoRef });
		characterIdGenerator++;
	}

	{
		Protocol::CharacterInfo* character = loginPkt.add_chracters();
		character->set_characterid(characterIdGenerator);
		character->set_playertype(Protocol::PLAYER_TYPE_MAGE);
		character->set_name("IceMage123");
		character->set_level(1);
		character->set_hp(100);
		character->set_exp(0);
		character->set_attack(5);
		character->set_mapid(1);

		CharacterInfoRef characterInfoRef = MakeShared<CharacterInfo>(character);

		gameSession->characters.insert({ characterIdGenerator, characterInfoRef });
		characterIdGenerator++;
	}

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
	session->Send(sendBuffer);

	return true;
}

bool Handle_C_ENTER(PacketSessionRef& session, Protocol::C_ENTER& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	uint64 characterId = pkt.characterid();
	CharacterInfoRef characterInfo = gameSession->characters.at(characterId);

	static Atomic<uint64> playerIdGenerator = 1;

	if (characterInfo == nullptr) 
	{
		Protocol::S_ENTER enterPacket;
		enterPacket.set_success(false);
		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterPacket);
		session->Send(sendBuffer);
	}
	else 
	{
		PlayerRef player = MakeShared<Player>();
		player->playerId = playerIdGenerator++;
		player->characterId = characterInfo->characterId;
		player->playerType = characterInfo->playerType;
		player->name = characterInfo->name;
		player->playerState = CreatureState{ 0.0, 0.0, BaseState::IDLE, MoveDir::LEFT };
		player->ownerSession = gameSession;

		gameSession->player = player;
		GSessionManager.AddPlayer(player->playerId, player);

		{
			Protocol::S_ENTER enterPacket;
			enterPacket.set_success(true);

			Protocol::Player* myPlayer = new Protocol::Player();
			myPlayer->set_playerid(player->playerId);
			myPlayer->set_characterid(player->characterId);
			myPlayer->set_playertype((Protocol::PlayerType)player->playerType);
			myPlayer->set_name(player->name);

			Protocol::CreatureState* playerState = new Protocol::CreatureState();
			playerState->set_posx(player->playerState.posX);
			playerState->set_posy(player->playerState.posY);
			playerState->set_basestate((Protocol::BaseState)player->playerState.baseState);
			playerState->set_movedir((Protocol::MoveDir)player->playerState.moveDir);
			myPlayer->set_allocated_playerstate(playerState);

			enterPacket.set_allocated_myplayer(myPlayer);

			auto players = GGameMap->GetPlayers();
			for (auto& p : players)
			{
				Protocol::Player* otherPlayer = enterPacket.add_players();
				otherPlayer->set_playerid(p.second->playerId);
				otherPlayer->set_characterid(p.second->characterId);
				otherPlayer->set_playertype((Protocol::PlayerType)p.second->playerType);
				otherPlayer->set_name(p.second->name);

				Protocol::CreatureState* otherPlayerState = new Protocol::CreatureState();
				otherPlayerState->set_posx(p.second->playerState.posX);
				otherPlayerState->set_posy(p.second->playerState.posY);
				otherPlayerState->set_basestate((Protocol::BaseState)p.second->playerState.baseState);
				otherPlayerState->set_movedir((Protocol::MoveDir)p.second->playerState.moveDir);
				otherPlayer->set_allocated_playerstate(otherPlayerState);
			}

			auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterPacket);
			session->Send(sendBuffer);
		}

		{
			Protocol::S_ENTER_MAP enterMapPkt;
			Protocol::Player* enterPlayer = new Protocol::Player();
			enterPlayer->set_playerid(player->playerId);
			enterPlayer->set_characterid(player->characterId);
			enterPlayer->set_playertype((Protocol::PlayerType)player->playerType);
			enterPlayer->set_name(player->name);

			Protocol::CreatureState* playerState = new Protocol::CreatureState();
			playerState->set_posx(player->playerState.posX);
			playerState->set_posy(player->playerState.posY);
			playerState->set_basestate((Protocol::BaseState)player->playerState.baseState);
			playerState->set_movedir((Protocol::MoveDir)player->playerState.moveDir);
			enterPlayer->set_allocated_playerstate(playerState);

			enterMapPkt.set_allocated_player(enterPlayer);

			auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterMapPkt);
			GGameMap->Broadcast(sendBuffer);
		}

		GGameMap->DoAsync(&GameMap::Enter, player);
	}
	return true;
}

bool Handle_C_LEAVE(PacketSessionRef& session, Protocol::C_LEAVE& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	PlayerRef player = gameSession->player;
	if (player != nullptr) {
		GGameMap->Leave(player);

		uint64 playerId = player->playerId;

		Protocol::S_LEAVE leavePkt;
		leavePkt.set_playerid(playerId);
		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(leavePkt);
		
		GGameMap->Broadcast(sendBuffer);
	}

	return true;
}

bool Handle_C_MOVE_START(PacketSessionRef& session, Protocol::C_MOVE_START& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	PlayerRef player = gameSession->player;

	GGameMap->DoAsync(&GameMap::HandleMoveStart, player->playerId, pkt);
	return true;
}

bool Handle_C_MOVE_END(PacketSessionRef& session, Protocol::C_MOVE_END& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	PlayerRef player = gameSession->player;

	GGameMap->DoAsync(&GameMap::HandleMoveEnd, player->playerId, pkt);
	return true;
}

bool Handle_C_JUMP(PacketSessionRef& session, Protocol::C_JUMP& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	PlayerRef player = gameSession->player;

	GGameMap->DoAsync(&GameMap::HandleJump, player->playerId, pkt);
	return true;
}

bool Handle_C_JUMP_END(PacketSessionRef& session, Protocol::C_JUMP_END& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	PlayerRef player = gameSession->player;

	GGameMap->DoAsync(&GameMap::HandleJumpEnd, player->playerId, pkt);
	return true;
}

bool Handle_C_SKILL(PacketSessionRef& session, Protocol::C_SKILL& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	PlayerRef player = gameSession->player;

	GGameMap->DoAsync(&GameMap::HandleSkill, player->playerId, pkt);
	return true;
}


