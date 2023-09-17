#pragma once
#include "Vector2D.hpp"

class Transform
{
public:
    float X, Y;
    Transform(float x = 0, float y = 0): X(x), Y(y) {};

    inline void TranslateX(float x){X += x;}
    inline void TranslateY(float y){Y += y;}
    inline void TranslateX(Vector2D v){X += v.X; Y += v.Y;}
};