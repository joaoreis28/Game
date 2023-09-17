#pragma once
#include "Character.hpp"
#include "Animation.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "Vector2D.hpp"
#include "CollisionHandler.hpp"

#define JUMP_TIME  15.0f
#define JUMP_FORCE 10.0f


#define ATTACK_TIME  20.0f
#define RUN_FORCE 4.0f


class Warrior: public Character
{

public:
    Warrior(Properties* props);
    virtual void Draw();
    virtual void Clean();
    virtual void Update(float dt);
private:

    void AnimationState();

    bool m_IsRunning;
    bool m_IsJumping;
    bool m_IsFalling;
    bool m_IsGrounded;
    bool m_IsAttacking;
    bool m_IsCrounching;

    float m_JumpTime;
    float m_JumpForce;
    float m_AttackTiime;

    Collider* m_Collider;
    Vector2D m_LastSafePosition;//talvez seja ponteiro
    RigidBody* m_RigidBody;
    Animation* m_Animation;
};