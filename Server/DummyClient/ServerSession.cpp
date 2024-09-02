#include "pch.h"
#include "ServerSession.h"
#include "ServerPacketHandler.h"

ServerSession::~ServerSession()
{
	cout << "~ServerSession" << endl;
}

void ServerSession::OnConnected()
{
	cout << "Server Connected!" << endl;

	Protocol::C_CHAT chatPacket;
	chatPacket.set_msg("Hello, Server!");
	SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPacket);
	Send(sendBuffer);
}

void ServerSession::OnDisconnected()
{
	cout << "Server Disconnected!" << endl;
}

void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketSessionRef session = GetPacketSessionRef();
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	cout << "Server Recv!" << endl;
	ServerPacketHandler::HandlePacket(session, buffer, len);
}

void ServerSession::OnSend(int32 len)
{
	cout << "Server Send!" << endl;
}

