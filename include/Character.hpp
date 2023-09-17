#pragma once
#include "GameObject.hpp"
#include <string>

class Character: public GameObject
{

public:
    Character(Properties* props): GameObject(props){};
    virtual void Clean() = 0;
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;

protected:
    std::string  m_Name;


};