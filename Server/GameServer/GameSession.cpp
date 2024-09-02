#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"
#include "GameMap.h"

GameSession::~GameSession()
{
}

void GameSession::OnConnected()
{
	GSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));

	cout << "Client Connected" << endl;
}

void GameSession::OnDisconnected()
{
	GSessionManager.Remove(static_pointer_cast<GameSession>(shared_from_this()));

	if (player != nullptr) 
	{
		GGameMap->DoAsync(&GameMap::Leave, player);

		Protocol::S_LEAVE leavePkt;
		leavePkt.set_playerid(player->playerId);
		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(leavePkt);
		GGameMap->Broadcast(sendBuffer);
	}

	cout << "Client Disconnected" << endl;
}

void GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	ClientPacketHandler::HandlePacket(session, buffer, len);
}

void GameSession::OnSend(int32 len)
{
}