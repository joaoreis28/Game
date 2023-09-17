#include "Engine.hpp"
#include "TextureManager.hpp"
#include "Warrior.hpp"
#include "Input.hpp"
#include "Timer.hpp"
#include "MapParser.hpp"
#include "Camera.hpp"


Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

Engine* Engine::GetInstance()
{
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
}


bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Failed to initialize sdl : %s ", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("Receba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH ,SCREEN_HEIGHT, window_flags);
    if(m_Window == nullptr)
    {
        SDL_Log("Failed to create Window sdl : %s ", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr)
    {
        SDL_Log("Failed to create Render sdl : %s ", SDL_GetError());
        return false;
    }

    if (!MapParser::GetInstance()->Load())
    {
        std::cout << "Failed to load Map" << std::endl;
        return false;
    }
    
    m_LevelMap = MapParser::GetInstance()->GetMaps("level1");
  TextureManager::GetInstance()->ParseTexture("assests/textures.xml");  
/*
    TextureManager::GetInstance()->Load("player_idle","assests/Idle.png");
    TextureManager::GetInstance()->Load("player_run","assests/Samurai/Run.png");
    TextureManager::GetInstance()->Load("player_jump","assests/Samurai/Jump.png");
    TextureManager::GetInstance()->Load("player_fall","assests/Samurai/Fall.png");
    TextureManager::GetInstance()->Load("player_crouch","assests/Samurai/Attack1.png");
    TextureManager::GetInstance()->Load("player_attack","assests/Samurai/Attack2.png");

    TextureManager::GetInstance()->Load("bg", "assests/Background.png");*/
    player = new Warrior(new Properties("player", 400, 200, 200, 200));


    Camera::GetInstance()->SetTarget(player->GetOrigin());
    return m_Isrunning = true;
}

bool Engine::Clean()
{
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_Isrunning = false;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    player->Update(dt);   

    Camera::GetInstance()->Update(dt);
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 0);
    SDL_RenderClear(m_Renderer);

    TextureManager::GetInstance()->Draw("bg", 0, 0, 2100, 1050,1, 1, 0.5);
    m_LevelMap->Render();

    player->Draw();
    SDL_RenderPresent(m_Renderer);
    
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}
