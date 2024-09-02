#pragma once

class GameSession;

using GameSessionRef = shared_ptr<GameSession>;

class GameSessionManager
{
public:
	void Add(GameSessionRef session);
	void Remove(GameSessionRef session);
	void Broadcast(SendBufferRef sendBuffer);

	unordered_map<int, PlayerRef> GetPlayers();
	PlayerRef GetPlayer(int playerId);

	void AddPlayer(int playerId, PlayerRef player);

private:
	USE_LOCK;
	Set<GameSessionRef> _sessions;	

	unordered_map<int, PlayerRef> _players;
};

extern GameSessionManager GSessionManager;
