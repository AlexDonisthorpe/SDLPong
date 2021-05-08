//
//  Game.cpp
//  SDL Pong
//
//  Created by Alex Donisthorpe on 08/05/2021.
//

#include <stdio.h>
#include "Game.h"

Game::Game()
{
    
}

bool Game::Initialize()
{
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    
    if(sdlResult != 0)
    {
        SDL_Log("SDL couldn't initialize: %s", SDL_GetError());
        return false;
    }
    
    mWindow = SDL_CreateWindow(
                     "SDLPong", // Window Name
                     100, // Top-left x pos
                     100, // Top-left y pos
                     1024, // width (pixels)
                     768, // height (pixels)
                     0 // special flags?
                     );
    
    if(!mWindow)
    {
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return false;
    }
    
    
    
    SDL_Log("Game Initialised");
    return true;
    
}

void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop()
{
    while(mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event Event;
    
    // If the user tries to close the application via UI
    while(SDL_PollEvent(&Event))
    {
        switch(Event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
    
    // get keyboard state
    const Uint8* state = SDL_GetKeyboardState(NULL);
    
    // If they hit escape, quit
    if(state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::UpdateGame()
{
    
}

void Game::GenerateOutput()
{
    
}
