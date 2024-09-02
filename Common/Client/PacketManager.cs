using Google.Protobuf;
using Google.Protobuf.Protocol;
using ServerCore;
using System;
using System.Collections.Generic;

public enum MsgId
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
}

class PacketManager
{
	#region Singleton
	static PacketManager _instance = new PacketManager();
	public static PacketManager Instance { get { return _instance; } }
	#endregion

	PacketManager()
	{
		Register();
	}

	Dictionary<ushort, Action<PacketSession, ArraySegment<byte>, ushort>> _onRecv = new Dictionary<ushort, Action<PacketSession, ArraySegment<byte>, ushort>>();
	Dictionary<ushort, Action<PacketSession, IMessage>> _handler = new Dictionary<ushort, Action<PacketSession, IMessage>>();
		
	public Action<PacketSession, IMessage, ushort> CustomHandler { get; set; }

	public void Register()
	{
		_onRecv.Add((ushort)MsgId.PKT_S_CHAT, MakePacket<S_CHAT>);
		_handler.Add((ushort)MsgId.PKT_S_CHAT, PacketHandler.S_CHAT_Handler);
		_onRecv.Add((ushort)MsgId.PKT_S_LOGIN, MakePacket<S_LOGIN>);
		_handler.Add((ushort)MsgId.PKT_S_LOGIN, PacketHandler.S_LOGIN_Handler);
		_onRecv.Add((ushort)MsgId.PKT_S_ENTER, MakePacket<S_ENTER>);
		_handler.Add((ushort)MsgId.PKT_S_ENTER, PacketHandler.S_ENTER_Handler);
		_onRecv.Add((ushort)MsgId.PKT_S_ENTER_MAP, MakePacket<S_ENTER_MAP>);
		_handler.Add((ushort)MsgId.PKT_S_ENTER_MAP, PacketHandler.S_ENTER_MAP_Handler);
		_onRecv.Add((ushort)MsgId.PKT_S_LEAVE, MakePacket<S_LEAVE>);
		_handler.Add((ushort)MsgId.PKT_S_LEAVE, PacketHandler.S_LEAVE_Handler);
		_onRecv.Add((ushort)MsgId.PKT_S_MOVE_START, MakePacket<S_MOVE_START>);
		_handler.Add((ushort)MsgId.PKT_S_MOVE_START, PacketHandler.S_MOVE_START_Handler);
		_onRecv.Add((ushort)MsgId.PKT_S_MOVE_END, MakePacket<S_MOVE_END>);
		_handler.Add((ushort)MsgId.PKT_S_MOVE_END, PacketHandler.S_MOVE_END_Handler);
		_onRecv.Add((ushort)MsgId.PKT_S_JUMP, MakePacket<S_JUMP>);
		_handler.Add((ushort)MsgId.PKT_S_JUMP, PacketHandler.S_JUMP_Handler);
		_onRecv.Add((ushort)MsgId.PKT_S_JUMP_END, MakePacket<S_JUMP_END>);
		_handler.Add((ushort)MsgId.PKT_S_JUMP_END, PacketHandler.S_JUMP_END_Handler);
		_onRecv.Add((ushort)MsgId.PKT_S_SKILL, MakePacket<S_SKILL>);
		_handler.Add((ushort)MsgId.PKT_S_SKILL, PacketHandler.S_SKILL_Handler);
	}

	public void OnRecvPacket(PacketSession session, ArraySegment<byte> buffer)
	{
		ushort count = 0;

		ushort size = BitConverter.ToUInt16(buffer.Array, buffer.Offset);
		count += 2;
		ushort id = BitConverter.ToUInt16(buffer.Array, buffer.Offset + count);
		count += 2;

		Action<PacketSession, ArraySegment<byte>, ushort> action = null;
		if (_onRecv.TryGetValue(id, out action))
			action.Invoke(session, buffer, id);
	}

	void MakePacket<T>(PacketSession session, ArraySegment<byte> buffer, ushort id) where T : IMessage, new()
	{
		T pkt = new T();
		pkt.MergeFrom(buffer.Array, buffer.Offset + 4, buffer.Count - 4);

		if (CustomHandler != null)
		{
			CustomHandler.Invoke(session, pkt, id);
		}
		else
		{
			Action<PacketSession, IMessage> action = null;
			if (_handler.TryGetValue(id, out action))
				action.Invoke(session, pkt);
		}
	}

	public Action<PacketSession, IMessage> GetPacketHandler(ushort id)
	{
		Action<PacketSession, IMessage> action = null;
		if (_handler.TryGetValue(id, out action))
			return action;
		return null;
	}
}