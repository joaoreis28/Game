#include "Warrior.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include "Input.hpp"
#include "Camera.hpp"
#include <iostream>

Warrior::Warrior(Properties* props):Character(props)
{
    m_IsRunning = false;
    m_IsJumping = false;
    m_IsFalling = false;
    m_IsGrounded = false;
    m_IsAttacking = false;
    m_IsCrounching = false;


    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTiime = ATTACK_TIME;
    m_Flip = SDL_FLIP_NONE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-80,-60,60,30);///deixar super fino  (-70,-20,20,0) (0,0,afina,0)

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 4, 100);
}



void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRender(), &box);
}

void Warrior::Update(float dt)
{
    m_IsRunning = false;
    m_IsCrounching = false;
    m_RigidBody->UnsetForce();

    //Run forward
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(FORWARD*RUN_FORCE);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning  = true;
    }

    //Run backward
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(BACKWARD*RUN_FORCE);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }
    
    //Crouch
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
        m_RigidBody->UnsetForce();
        m_IsCrounching = true;
    }

    //Attack
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K))
    {
        m_RigidBody->UnsetForce();
        m_IsAttacking = true;       
    }
    
    //Jump
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsGrounded)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsJumping && m_JumpTime > 0)
    {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    else
        {
            m_IsJumping = false;
            m_JumpTime = JUMP_TIME;
        }

    //Fall
    if(m_RigidBody->GetVelocity().Y > 0 && !m_IsGrounded)
        m_IsFalling = true;
    else
        m_IsFalling = false;

    //Attack Timer
    if(m_IsAttacking && m_AttackTiime > 0)
    {
        m_AttackTiime -= dt;
    }
    else
        {
            m_IsAttacking = false;
            m_AttackTiime = ATTACK_TIME;
        }

    //move on x axis          
    m_RigidBody->Update(dt);//colocar dt
    m_LastSafePosition.X = m_Transform->X;
    
    m_Transform->X += m_RigidBody->GetPosition().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);

   if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {

        m_Transform->X = m_LastSafePosition.X;
        
        
    }


    //move on y axis
    m_RigidBody->Update(dt);//colocar dt
    m_LastSafePosition.Y = m_Transform->Y;
    
    m_Transform->Y += m_RigidBody->GetPosition().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 96);// 18, 50

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
        
    }
    else
    {
        m_IsGrounded = false;
    }


    

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    AnimationState();
    m_Animation->Update();

    
}

void Warrior::AnimationState()
{
    //Idle
    m_Animation->SetProps("player_idle", 0, 4, 100);//existe o mundo que seja 1 no lugar do zero

    //runnig
    if(m_IsRunning)
        m_Animation->SetProps("player_run", 0, 8, 100);

    //Crouching
    if(m_IsCrounching)
        m_Animation->SetProps("player_crouch", 0, 4, 200);

    //jumping
    if(m_IsJumping)
        m_Animation->SetProps("player_jump", 0, 2, 200);

    //falling
    if(m_IsFalling)
        m_Animation->SetProps("player_fall", 0,1, 350);
    
    //attacking
    if(m_IsAttacking)
        m_Animation->SetProps("player_attack", 0, 4, 80);

}
void Warrior::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);//dsd 
}