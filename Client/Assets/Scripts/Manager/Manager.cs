using UnityEngine;

public class Manager : MonoBehaviour
{
    static Manager s_instance;
    static Manager Instance { get { return s_instance; } }

    NetworkManager _network = new NetworkManager();
    SceneDataManager _scene = new SceneDataManager();
    GameManager _game = new GameManager();

    public static NetworkManager Network { get { return Instance._network; } }
    public static SceneDataManager Scene { get { return Instance._scene; } }
    public static GameManager Game { get { return Instance._game; } }

    void Start()
    {
        Init();
    }

    void Update()
    {
        _network.Update();
    }

    static void Init()
    {
        if (s_instance == null)
        {
            GameObject go = GameObject.Find("@Managers");
            if (go == null)
            {
                go = new GameObject { name = "@Managers" };
                go.AddComponent<Manager>();
            }

            DontDestroyOnLoad(go);
            s_instance = go.GetComponent<Manager>();

            s_instance._network.Init();
        }
    }
}