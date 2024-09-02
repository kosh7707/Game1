using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CharacterSelectUIHandler : MonoBehaviour
{
    [SerializeField]
    List<GameObject> characterSlot = new();

    List<Character> _characters = new();

    string prefabPath = "CharacterSelectScreen/";

    int _selectCharacterIndex = 0;
    public int SelectCharacterIndex { get { return _selectCharacterIndex; } set { _selectCharacterIndex = value; } }

    void Start()
    {
        ProcessLoginPacket();
        CharacterVisualize();
    }

    void Update()
    {

    }

    private void ProcessLoginPacket()
    {
        S_LOGIN loginPkt = Manager.Scene.LoginPkt;
        if (loginPkt == null)
        {
            Debug.Log("loginPkt is null.");
            return;
        }

        foreach (var characterInfo in loginPkt.Chracters)
        {
            Character character = new Character(characterInfo);
            _characters.Add(character);
        }
    }

    private void CharacterVisualize()
    {
        for (int i = 0; i < _characters.Count; i++)
        {
            GameObject characterPrefab;
            switch (_characters[i].PlayerType)
            {
                case PlayerType.PLAYER_TYPE_KNIGHT:
                    characterPrefab = Resources.Load<GameObject>(prefabPath + "Character_1");
                    break;
                case PlayerType.PLAYER_TYPE_ARCHER:
                    characterPrefab = Resources.Load<GameObject>(prefabPath + "Character_2");
                    break;
                case PlayerType.PLAYER_TYPE_MAGE:
                    characterPrefab = Resources.Load<GameObject>(prefabPath + "Character_3");
                    break;
                default:
                    characterPrefab = Resources.Load<GameObject>(prefabPath + "Character_1");
                    break;
            }
            Instantiate(characterPrefab, characterSlot[i].transform.position, Quaternion.identity, characterSlot[i].transform);
        }
    }

    public void ProcessEnter()
    {
        C_ENTER enterPkt = new C_ENTER();
        enterPkt.CharacterId = _characters[SelectCharacterIndex].CharacterId;
        Manager.Network.Send(enterPkt);
    }

    public void ProcessEnterPacket(S_ENTER pkt)
    {
        if (pkt.Success)
            ProcessEnterSuccess(pkt);
        else
            ProcessEnterFail(pkt);
    }
    public void ProcessEnterSuccess(S_ENTER pkt)
    {
        Debug.Log("ProcessEnterSuccess");

        Manager.Scene.EnterPkt = pkt;
        SceneManager.LoadScene("Map01");
    }

    public void ProcessEnterFail(S_ENTER pkt)
    {
        Debug.Log("ProcessEnterFail");
    }
}
