#pragma once

#include "SDL2/SDL.h"



class Collider
{
private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;

public:
    inline SDL_Rect Get(){return m_Box;}
    inline void SetBuffer(int x, int y, int w, int h){m_Buffer = {x, y, w, h};}

    void Set(int x, int y, int w, int h)
    {
        m_Box = {x - m_Buffer.x, y - m_Buffer.y, w - m_Buffer.w, h - m_Buffer.h};
    }

};