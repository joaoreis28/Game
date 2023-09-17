#include "Animation.hpp"
#include "TextureManager.hpp"

void Animation::Update()
{
    m_CurrentFrame = (SDL_GetTicks()/m_Speed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spritWidth, int spritHeight, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureId, x, y, spritWidth, spritHeight, m_SpriteRow, m_CurrentFrame, flip);
}


void Animation::SetProps(std::string textureID, int spritRow, int frameCount,  int animSpedd)
{
    m_TextureId = textureID;
    m_SpriteRow = spritRow;
    m_FrameCount = frameCount;
    m_Speed = animSpedd;
    
}