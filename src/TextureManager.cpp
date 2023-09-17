#include "TextureManager.hpp"
#include "Camera.hpp"
#include "tinyxml.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr)
    {
        SDL_Log("Failed to load texture : %s ", SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), surface);
    if(texture == nullptr)
    {
        SDL_Log("Failed to create texture from surface : %s ", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    
    return true;
}


void TextureManager::Draw(std::string id, int x, int y, int widht, int height,float scaleX, float scaleY ,float scroolRatio, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, widht, height};
    Vector2D cam = Camera::GetInstance()->GetPosition() * scroolRatio;


    SDL_Rect dstRect = {x- cam.X, y - cam.Y, widht*scaleX, height*scaleY};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);

}

void TextureManager::DrawFrame(std::string id, int x, int y, int widht, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect  srcRect = {widht* frame, height*row, widht, height};
    Vector2D cam = Camera::GetInstance()->GetPosition();


    SDL_Rect dstRect = {x- cam.X, y - cam.Y, widht, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);

}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}


void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }

    m_TextureMap.clear();
}


void TextureManager::DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip )
{
    
    SDL_Rect srcRect = {tilesize*frame, tilesize*(row ), tilesize, tilesize}; 
    Vector2D cam = Camera::GetInstance()->GetPosition();

    SDL_Rect dstRect = {x - cam.X, y - cam.Y, tilesize, tilesize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);

}

bool TextureManager::ParseTexture(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
    {
        std::cout << "Failed to Load :" << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e = root->FirstChildElement(); e!= nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("texture"))
        {
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            Load(id, src);
        }
    }
    return true;
}