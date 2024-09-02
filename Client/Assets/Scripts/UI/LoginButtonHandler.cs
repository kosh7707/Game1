using UnityEngine;
using TMPro;
using UnityEngine.UI;
using Google.Protobuf.Protocol;

public class LoginButtonHandler : MonoBehaviour
{
    [SerializeField] TMP_InputField idInput;
    [SerializeField] TMP_InputField pwInput;

    Button loginButton;

    void Awake()
    {
        loginButton = GetComponent<Button>();

        loginButton.onClick.AddListener(OnLoginButtonClick);
    }

    public void OnLoginButtonClick()
    {
        string username = idInput.text;
        string password = pwInput.text;

        if (username == "" || password == "")
            return;

        Debug.Log($"Username: {username}");
        Debug.Log($"Password: {password}");

        C_LOGIN loginPkt = new C_LOGIN();
        loginPkt.Id = username;
        loginPkt.Pw = password;
        Manager.Network.Send(loginPkt);

        loginButton.interactable = false;
        idInput.interactable = false;
        pwInput.interactable = false;
    }
}