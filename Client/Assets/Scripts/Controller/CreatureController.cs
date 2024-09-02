using Google.Protobuf.Protocol;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;

public abstract class CreatureController : MonoBehaviour
{
    protected Animator _animator;
    protected SpriteRenderer _spriteRenderer;

    public int Id { get; set; }
    public string Name { get; set; }

    protected float _movecConstant;
    protected float _lastJumpTime;
    protected bool _isGrounded = true;

    CreatureState _creatureState = new CreatureState();

    public virtual BaseState BehaviorState
    {
        get { return _creatureState.BaseState; }
        set
        {
            if (_creatureState.BaseState == value)
                return;

            _creatureState.BaseState = value;
            if (BehaviorState == BaseState.Jump)
            {
                _lastJumpTime = Time.time;
                _isGrounded = false;
            }
                

            UpdateAnimation();
        }
    }

    public virtual MoveDir Dir
    {
        get { return State.MoveDir; }
        set
        {
            if (State.MoveDir == value) 
                return;

            State.MoveDir = value;
            UpdateAnimation();
        }
    }

    public virtual Vector2 Position
    {
        get { return new Vector2(State.PosX, State.PosY); }
        set
        {
            if (State.PosX == value.x && State.PosY == value.y)
                return;

            State.PosX = value.x;
            State.PosY = value.y;
            transform.position = (Vector3)value;

        }
    }

    public virtual CreatureState State
    {
        get { return _creatureState; }
        set
        {
            if (_creatureState.Equals(value))
                return;

            BehaviorState = value.BaseState;
            Dir = value.MoveDir;
            Position = new Vector2(value.PosX, value.PosY);

            UpdateAnimation();
        }
    }

    protected abstract void UpdateAnimation();

    protected virtual void UpdateBehavior()
    {
        switch (BehaviorState)
        {
            case BaseState.Idle:
                UpdateIdle();
                break;
            case BaseState.Moving:
                UpdateMoving();
                break;
            case BaseState.Skill:
                UpdateSkill();
                break;
            case BaseState.Dead:
                UpdateDead();
                break;
            case BaseState.Jump:
                UpdateJump();
                break;
        }
    }

    protected abstract void UpdateIdle();

    protected abstract void UpdateMoving();

    protected abstract void UpdateSkill();

    protected abstract void UpdateDead();

    protected abstract void UpdateJump();

    protected virtual void Init()
    {
        _animator = GetComponent<Animator>();
        _spriteRenderer = GetComponent<SpriteRenderer>();
        UpdateAnimation();
    }

    void Start()
    {
        Init();
    }

    void Update()
    {
        UpdateBehavior();
    }
}
