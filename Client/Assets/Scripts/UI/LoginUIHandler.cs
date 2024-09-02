using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using TMPro;
using Google.Protobuf.Protocol;
using UnityEngine.SceneManagement;

public class LoginUIHandler : MonoBehaviour
{
    [SerializeField] TMP_InputField   idInput;
    [SerializeField] TMP_InputField   pwInput;
    [SerializeField] Button           loginButton;

    int _inputSelected = 0;

    void Awake()
    {
        idInput.text = "";
        pwInput.text = "";
    }

    void Update()
    {
        InputTabProcess();
        InputEnterProcess();
    }

    void InputTabProcess()
    {
        if (Input.GetKeyDown(KeyCode.Tab))
        {
            _inputSelected = (_inputSelected + 1) % 2;

            switch (_inputSelected)
            {
                case 0:
                    idInput.Select();
                    break;
                case 1:
                    pwInput.Select();
                    break;
            }
        }

    }

    void InputEnterProcess()
    {
        if (Input.GetKeyDown(KeyCode.Return))
        {
            loginButton.onClick.Invoke();
        }
    }

    public void ProcessLogin(S_LOGIN loginPkt)
    {
        if (loginPkt.Success)
            ProcessLoginSuccess(loginPkt);
        else
            ProcessLoginFail(loginPkt);
    }

    public void ProcessLoginSuccess(S_LOGIN loginPkt)
    {
        Debug.Log("ProcessLoginSuccess");

        Manager.Scene.LoginPkt = loginPkt;
        SceneManager.LoadScene("CharacterSelectScreen");
    }

    public void ProcessLoginFail(S_LOGIN loginPkt)
    {
        Debug.Log("ProcessLoginFail");

        loginButton.interactable = true;
        idInput.interactable = true;
        pwInput.interactable = true;
    }
}
