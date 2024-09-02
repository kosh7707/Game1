#include "pch.h"
#include "GameSessionManager.h"
#include "GameSession.h"
#include "Player.h"
#include "CharacterInfo.h"

GameSessionManager GSessionManager;

void GameSessionManager::Add(GameSessionRef session)
{
	WRITE_LOCK;
	_sessions.insert(session);
}

void GameSessionManager::Remove(GameSessionRef session)
{
	WRITE_LOCK;
	_sessions.erase(session);
}

void GameSessionManager::Broadcast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for (GameSessionRef session : _sessions)
	{
		session->Send(sendBuffer);
	}
}

unordered_map<int, PlayerRef> GameSessionManager::GetPlayers()
{
	return _players;
}

PlayerRef GameSessionManager::GetPlayer(int playerId)
{
	return _players[playerId];
}

void GameSessionManager::AddPlayer(int playerId, PlayerRef player)
{
	_players.insert({ playerId, player });
}
