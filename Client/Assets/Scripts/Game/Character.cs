using System;
using Google.Protobuf.Protocol;
public enum PlayerType
{
    PLAYER_TYPE_NONE = 0,
    PLAYER_TYPE_KNIGHT = 1,
    PLAYER_TYPE_MAGE = 2,
    PLAYER_TYPE_ARCHER = 3,
}

public class Character
{
    public ulong CharacterId { get; set; }
    public PlayerType PlayerType { get; set; }
    public string Name { get; set; }
    public uint Level { get; set; }
    public int Hp { get; set; }
    public int Exp { get; set; }
    public uint Attack { get; set; }
    public uint MapId { get; set; }

    public Character(ulong characterId, PlayerType playerType, string name, uint level, int hp, int exp, uint attack, uint mapId)
    {
        CharacterId = characterId;
        PlayerType = playerType;
        Name = name;
        Level = level;
        Hp = hp;
        Exp = exp;
        Attack = attack;
        MapId = mapId;
    }

    public Character(CharacterInfo characterInfo)
    {
        CharacterId = characterInfo.CharacterId;
        PlayerType = (PlayerType)characterInfo.PlayerType;
        Name = characterInfo.Name;
        Level = characterInfo.Level;
        Hp = characterInfo.Hp;
        Exp = characterInfo.Exp;
        Attack = characterInfo.Attack;
        MapId = characterInfo.MapId;
    }
}