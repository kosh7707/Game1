using UnityEngine;
using UnityEngine.EventSystems;

public class Touch : MonoBehaviour, IPointerDownHandler
{
    BoxCollider2D _boxCollider;
    CharacterSelectUIHandler _characterSelectUIHandler;

    public int _index = 0;

    void Awake()
    {
        _boxCollider = GetComponent<BoxCollider2D>();
        _characterSelectUIHandler = GameObject.Find("CharacterSelectUI").GetComponent<CharacterSelectUIHandler>();
    }

    public void OnPointerDown(PointerEventData eventData)
    {
        _characterSelectUIHandler.SelectCharacterIndex = _index;
    }
}