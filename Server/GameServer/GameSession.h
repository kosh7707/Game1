#pragma once
#include "Protocol.pb.h"
#include "CharacterInfo.h"
#include "Player.h"

class GameSession : public PacketSession
{
public:
	~GameSession();

	virtual void	OnConnected() override;
	virtual void	OnDisconnected() override;
	virtual void	OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void	OnSend(int32 len) override;

public:
	unordered_map<int, CharacterInfoRef> characters;
	PlayerRef player;
};

