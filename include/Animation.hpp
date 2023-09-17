#pragma once
#include <string>
#include "SDL2/SDL_image.h"

class Animation
{

public:
    Animation(){};
    void Update();
    void Draw(float x, float y, int spritWidth, int spritHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetProps(std::string textureID, int spritRow, int frameCount, int animSpedd);

private:
    int m_SpriteRow, m_CurrentFrame;
    int m_Speed, m_FrameCount;
    std::string m_TextureId;


};