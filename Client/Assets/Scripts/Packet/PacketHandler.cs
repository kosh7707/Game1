using Google.Protobuf;
using Google.Protobuf.Protocol;
using ServerCore;
using System;
using UnityEngine;

class PacketHandler
{
    public static void S_CHAT_Handler(PacketSession session, IMessage packet)
    {
        S_CHAT chatPkt = packet as S_CHAT;
        ServerSession serverSession = session as ServerSession;

        if (chatPkt.Success)
        {
            Debug.Log("[Server]: " + chatPkt.Msg);
        }
    }

    public static void S_LOGIN_Handler(PacketSession session, IMessage packet)
    {
        S_LOGIN loginPkt = packet as S_LOGIN;
        ServerSession serverSession = session as ServerSession;

        GameObject go = GameObject.Find("LoginUI");
        if (go == null)
            return;

        LoginUIHandler loginUIHandler = go.GetComponent<LoginUIHandler>();
        if (loginUIHandler == null)
            return;

        loginUIHandler.ProcessLogin(loginPkt);

    }

    public static void S_ENTER_Handler(PacketSession session, IMessage packet)
    {
        S_ENTER enterPkt = packet as S_ENTER;
        ServerSession serverSession = session as ServerSession;

        GameObject go = GameObject.Find("CharacterSelectUI");
        if (go == null) return;

        CharacterSelectUIHandler characterSelectUIHandler = go.GetComponent<CharacterSelectUIHandler>();
        characterSelectUIHandler.ProcessEnterPacket(enterPkt);

    }

    public static void S_LEAVE_Handler(PacketSession session, IMessage packet)
    {
        S_LEAVE leavePkt = packet as S_LEAVE;
        ServerSession serverSession = session as ServerSession;

        GameObject go = GameObject.Find($"Player_{leavePkt.PlayerId}");
        GameObject.Destroy(go);
    }

    public static void S_ENTER_MAP_Handler(PacketSession session, IMessage packet)
    {
        S_ENTER_MAP leavePkt = packet as S_ENTER_MAP;
        ServerSession serverSession = session as ServerSession;

        Player player = leavePkt.Player;

        Vector3 SpawnPosition = new Vector3(player.PlayerState.PosX, player.PlayerState.PosY, 0);
        GameObject PlayerPrefab = Resources.Load<GameObject>("Prefabs/Character/Player");
        GameObject go = UnityEngine.Object.Instantiate(PlayerPrefab, SpawnPosition, Quaternion.identity);
        go.name = "Player_" + player.PlayerId;
    }

    public static void S_MOVE_START_Handler(PacketSession session, IMessage packet)
    {
        S_MOVE_START moveStartPkt = packet as S_MOVE_START;
        ServerSession serverSession = session as ServerSession;

        if (moveStartPkt.PlayerId != Manager.Game.PlayerId)
        {
            GameObject go = GameObject.Find($"Player_{moveStartPkt.PlayerId}");
            PlayerController pc = go.GetComponent<PlayerController>();
            pc.State = moveStartPkt.State;
        }
    }

    public static void S_MOVE_END_Handler(PacketSession session, IMessage packet)
    {
        S_MOVE_END moveEndPacket = packet as S_MOVE_END;
        ServerSession serverSession = session as ServerSession;

        if (moveEndPacket.PlayerId != Manager.Game.PlayerId)
        {
            GameObject go = GameObject.Find($"Player_{moveEndPacket.PlayerId}");
            PlayerController pc = go.GetComponent<PlayerController>();
            pc.State = moveEndPacket.State;
        }
    }

    public static void S_JUMP_Handler(PacketSession session, IMessage packet)
    {
        S_JUMP jumpPkt = packet as S_JUMP;
        ServerSession serverSession = session as ServerSession;

        if (jumpPkt.Success)
        {            
            if (jumpPkt.PlayerId == Manager.Game.PlayerId)
            {
                GameObject go = GameObject.Find($"MyPlayer_{jumpPkt.PlayerId}");
                MyPlayerController mpc = go.GetComponent<MyPlayerController>();
                mpc.State = jumpPkt.State;
            }
            else
            {
                GameObject go = GameObject.Find($"Player_{jumpPkt.PlayerId}");
                PlayerController pc = go.GetComponent<PlayerController>();
                pc.State = jumpPkt.State;
            }
        }
    }

    public static void S_JUMP_END_Handler(PacketSession session, IMessage packet)
    {
        S_JUMP_END jumpEndPkt = packet as S_JUMP_END;
        ServerSession serverSession = session as ServerSession;

        if (jumpEndPkt.PlayerId == Manager.Game.PlayerId)
        {
            GameObject go = GameObject.Find($"MyPlayer_{jumpEndPkt.PlayerId}");
            MyPlayerController mpc = go.GetComponent<MyPlayerController>();
            mpc.State = jumpEndPkt.State;
        }
        else
        {
            GameObject go = GameObject.Find($"Player_{jumpEndPkt.PlayerId}");
            PlayerController pc = go.GetComponent<PlayerController>();
            pc.State = jumpEndPkt.State;
        }
    }

    internal static void S_SKILL_Handler(PacketSession session, IMessage packet)
    {
        S_SKILL skillPkt = packet as S_SKILL;
        ServerSession serverSession = session as ServerSession;

        if (skillPkt.Success)
        {
            if (skillPkt.PlayerId == Manager.Game.PlayerId)
            {
                GameObject go = GameObject.Find($"MyPlayer_{skillPkt.PlayerId}");
                MyPlayerController mpc = go.GetComponent<MyPlayerController>();
                mpc.State = skillPkt.State;
                mpc.UseSkill();
            }
            else
            {
                GameObject go = GameObject.Find($"Player_{skillPkt.PlayerId}");
                PlayerController pc = go.GetComponent<PlayerController>();
                pc.State = skillPkt.State;
                pc.UseSkill();
            }
        }
    }
}


