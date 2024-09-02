using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Google.Protobuf.Protocol;

public class MyPlayerController : PlayerController
{
    bool _moveUpdated = false;

    void LateUpdate()
    {
        Camera.main.transform.position = new Vector3(transform.position.x, transform.position.y, -10);
    }

    public override MoveDir Dir 
    {   
        get { return base.Dir; }
        set
        {
            if (base.Dir == value)
                return;

            base.Dir = value;
            _moveUpdated = false;
        }
    }

    void GetDirInput()
    {
        if (BehaviorState != BaseState.Skill && _isGrounded)
        {
            ProcessMoveInput();
        }

        if (BehaviorState != BaseState.Skill && _isGrounded && Input.GetKeyDown(KeyCode.C))
        {
            ProcessJumpInput();
        }

        if (BehaviorState != BaseState.Skill && _isGrounded && Input.GetKeyDown(KeyCode.A))
        {
            ProcessSkillInput();
        }
    }

    private void ProcessJumpInput()
    {
        if (BehaviorState == BaseState.Idle || BehaviorState == BaseState.Moving)
        {
            SendJumpPacket();
        }
    }

    private void ProcessMoveInput()
    {
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            if (!_moveUpdated)
            {
                SendMoveStartPacket();
                _moveUpdated = true;
            }
            Dir = MoveDir.Left;
            BehaviorState = BaseState.Moving;
        }
        else if (Input.GetKey(KeyCode.RightArrow))
        {
            if (!_moveUpdated)
            {
                SendMoveStartPacket();
                _moveUpdated = true;
            }
            Dir = MoveDir.Right;
            BehaviorState = BaseState.Moving;
        }
        else
        {
            if (_moveUpdated)
            {
                SendMoveEndPacket();
                _moveUpdated = false;
            }
            BehaviorState = BaseState.Idle;
        }
    }

    private void ProcessSkillInput()
    {
        if (BehaviorState == BaseState.Idle || BehaviorState == BaseState.Moving)
        {
            SendSkillPacket();
        }
    }

    protected override void UpdateBehavior()
    {
        GetDirInput();

        base.UpdateBehavior();
    }

    protected override void UpdateIdle()
    {

    }

    void SendMoveStartPacket()
    {
        C_MOVE_START moveStartPkt = new C_MOVE_START();
        moveStartPkt.State = State;
        Manager.Network.Send(moveStartPkt);
    }

    void SendMoveEndPacket()
    {
        C_MOVE_END moveEndPkt = new C_MOVE_END();
        moveEndPkt.State = State;
        Manager.Network.Send(moveEndPkt);
    }
    
    void SendJumpPacket()
    {
        C_JUMP jumpPkt = new C_JUMP();
        jumpPkt.State = State;  
        Manager.Network.Send(jumpPkt);
    }

    protected override void UpdateJump()
    {
        base.UpdateJump();

        if (_isGrounded && BehaviorState == BaseState.Idle)
        {
            C_JUMP_END jumpEndPkt = new C_JUMP_END();
            jumpEndPkt.State = State;
            Manager.Network.Send(jumpEndPkt);

            if (_moveUpdated)
            {
                SendMoveStartPacket();
            }
        }
    }

    void SendSkillPacket()
    {
        C_SKILL skillPkt = new C_SKILL();   
        skillPkt.State = State;
        Manager.Network.Send(skillPkt);
    }

    public override void UseSkill()
    {
        base.UseSkill();
    }

    IEnumerator CoStartSkill()
    {
        BehaviorState = BaseState.Skill;
        yield return new WaitForSeconds(0.4f);
        BehaviorState = BaseState.Idle;
        _coSkill = null;

        SendMoveEndPacket();
        _moveUpdated = false;
    }
}
