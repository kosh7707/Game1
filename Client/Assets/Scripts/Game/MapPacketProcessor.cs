using Google.Protobuf.Protocol;
using UnityEngine;

public class MapPacketProcessor : MonoBehaviour
{
    string prefabPath = "Prefabs/Character/";

    void Start()
    {
        ProcessEnterPacket();
    }

    private void ProcessEnterPacket()
    {
        S_ENTER enterPkt = Manager.Scene.EnterPkt;

        {
            Vector3 SpawnPosition = new Vector3(enterPkt.MyPlayer.PlayerState.PosX, enterPkt.MyPlayer.PlayerState.PosY, 0);
            GameObject MyPlayerPrefab = Resources.Load<GameObject>(prefabPath + "MyPlayer");
            GameObject go = Instantiate(MyPlayerPrefab, SpawnPosition, Quaternion.identity);
            go.name = "MyPlayer_" + enterPkt.MyPlayer.PlayerId;
            Manager.Game.PlayerId = enterPkt.MyPlayer.PlayerId;

            MyPlayerController mpc = go.GetComponent<MyPlayerController>();
            mpc.State = enterPkt.MyPlayer.PlayerState;  
        }

        foreach (var player in enterPkt.Players)
        {
            Vector3 SpawnPosition = new Vector3(player.PlayerState.PosX, player.PlayerState.PosY, 0);
            GameObject PlayerPrefab = Resources.Load<GameObject>(prefabPath + "Player");
            GameObject go = Instantiate(PlayerPrefab, SpawnPosition, Quaternion.identity);
            go.name = "Player_" + player.PlayerId;

            PlayerController pc = go.GetComponent<PlayerController>();
            pc.State = player.PlayerState;
        }

    }
}