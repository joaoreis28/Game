#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameMap.hpp"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine {

public:
    
    //Singleton
    static Engine* GetInstance();

    bool Init();
    bool Clean();
    void Quit();

    void Update();
    void Render();
    void Events();

    inline GameMap* Getmap(){return m_LevelMap;}
    inline bool IsRunning(){return m_Isrunning;}
    inline SDL_Renderer* GetRender(){return m_Renderer;}
private:
    Engine(){};
    bool m_Isrunning;
    SDL_Window* m_Window;
    GameMap* m_LevelMap;
    SDL_Renderer* m_Renderer;
    static Engine* s_Instance;
};