#pragma once
#include "Protocol.pb.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
	PKT_C_CHAT = 1000,
	PKT_S_CHAT = 1001,
	PKT_C_LOGIN = 1002,
	PKT_S_LOGIN = 1003,
	PKT_C_ENTER = 1004,
	PKT_S_ENTER = 1005,
	PKT_C_LEAVE = 1006,
	PKT_S_ENTER_MAP = 1007,
	PKT_S_LEAVE = 1008,
	PKT_C_MOVE_START = 1009,
	PKT_S_MOVE_START = 1010,
	PKT_C_MOVE_END = 1011,
	PKT_S_MOVE_END = 1012,
	PKT_C_JUMP = 1013,
	PKT_S_JUMP = 1014,
	PKT_C_JUMP_END = 1015,
	PKT_S_JUMP_END = 1016,
	PKT_C_SKILL = 1017,
	PKT_S_SKILL = 1018,
};

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt);
bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt);
bool Handle_C_ENTER(PacketSessionRef& session, Protocol::C_ENTER& pkt);
bool Handle_C_LEAVE(PacketSessionRef& session, Protocol::C_LEAVE& pkt);
bool Handle_C_MOVE_START(PacketSessionRef& session, Protocol::C_MOVE_START& pkt);
bool Handle_C_MOVE_END(PacketSessionRef& session, Protocol::C_MOVE_END& pkt);
bool Handle_C_JUMP(PacketSessionRef& session, Protocol::C_JUMP& pkt);
bool Handle_C_JUMP_END(PacketSessionRef& session, Protocol::C_JUMP_END& pkt);
bool Handle_C_SKILL(PacketSessionRef& session, Protocol::C_SKILL& pkt);


class ClientPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
		GPacketHandler[PKT_C_CHAT] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_CHAT>(Handle_C_CHAT, session, buffer, len); };
		GPacketHandler[PKT_C_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_LOGIN>(Handle_C_LOGIN, session, buffer, len); };
		GPacketHandler[PKT_C_ENTER] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ENTER>(Handle_C_ENTER, session, buffer, len); };
		GPacketHandler[PKT_C_LEAVE] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_LEAVE>(Handle_C_LEAVE, session, buffer, len); };
		GPacketHandler[PKT_C_MOVE_START] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_MOVE_START>(Handle_C_MOVE_START, session, buffer, len); };
		GPacketHandler[PKT_C_MOVE_END] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_MOVE_END>(Handle_C_MOVE_END, session, buffer, len); };
		GPacketHandler[PKT_C_JUMP] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_JUMP>(Handle_C_JUMP, session, buffer, len); };
		GPacketHandler[PKT_C_JUMP_END] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_JUMP_END>(Handle_C_JUMP_END, session, buffer, len); };
		GPacketHandler[PKT_C_SKILL] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_SKILL>(Handle_C_SKILL, session, buffer, len); };		
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::S_CHAT& pkt) { return _MakeSendBuffer(pkt, PKT_S_CHAT); }
	static SendBufferRef MakeSendBuffer(Protocol::S_LOGIN& pkt) { return _MakeSendBuffer(pkt, PKT_S_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ENTER& pkt) { return _MakeSendBuffer(pkt, PKT_S_ENTER); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ENTER_MAP& pkt) { return _MakeSendBuffer(pkt, PKT_S_ENTER_MAP); }
	static SendBufferRef MakeSendBuffer(Protocol::S_LEAVE& pkt) { return _MakeSendBuffer(pkt, PKT_S_LEAVE); }
	static SendBufferRef MakeSendBuffer(Protocol::S_MOVE_START& pkt) { return _MakeSendBuffer(pkt, PKT_S_MOVE_START); }
	static SendBufferRef MakeSendBuffer(Protocol::S_MOVE_END& pkt) { return _MakeSendBuffer(pkt, PKT_S_MOVE_END); }
	static SendBufferRef MakeSendBuffer(Protocol::S_JUMP& pkt) { return _MakeSendBuffer(pkt, PKT_S_JUMP); }
	static SendBufferRef MakeSendBuffer(Protocol::S_JUMP_END& pkt) { return _MakeSendBuffer(pkt, PKT_S_JUMP_END); }
	static SendBufferRef MakeSendBuffer(Protocol::S_SKILL& pkt) { return _MakeSendBuffer(pkt, PKT_S_SKILL); }	
	
private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, pkt);
	}


	template<typename T>
	static SendBufferRef _MakeSendBuffer(T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);

		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;

		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));

		sendBuffer->Close(packetSize);
		return sendBuffer;
	}
};
