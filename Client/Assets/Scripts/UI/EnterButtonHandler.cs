using UnityEngine;
using UnityEngine.UI;

public class EnterButtonHandler : MonoBehaviour
{
    Button _enterButton;
    CharacterSelectUIHandler _characterSelectUIHandler;

    private void Awake()
    {
        _enterButton = GetComponent<Button>();

        _characterSelectUIHandler = GameObject.Find("CharacterSelectUI").GetComponent<CharacterSelectUIHandler>();

        _enterButton.onClick.AddListener(OnEnterButtonClick);
    }

    public void OnEnterButtonClick()
    {
        _characterSelectUIHandler.ProcessEnter();

    }
}