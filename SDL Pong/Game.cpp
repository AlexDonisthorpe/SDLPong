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
    
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(!mRenderer)
    {
        SDL_Log("Couldn't create renderer: %s", SDL_GetError());
        return false;
    }
    
    // Set Object Positions
    mBallPosition.x = 512;
    mBallPosition.y = 384;
    
    mLeftPaddlePosition.x = 30;
    mLeftPaddlePosition.y = 384;
    
    mRightPaddlePosition.x = 1024 - 30;
    mRightPaddlePosition.y = 384;
    
    
    SDL_Log("Game Initialised");
    return true;
    
}

void Game::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
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
    const Uint8* KeyboardState = SDL_GetKeyboardState(NULL);
    
    // If they hit escape, quit
    if(KeyboardState[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::GenerateOutput()
{
    
    
    // Set the renderer background color
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    
    // Clear the back buffer & fill with draw color
    SDL_RenderClear(mRenderer);
    
    // Set color of next object
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    
    SDL_Rect ceiling
    {
        0,
        0,
        1024,
        thickness
    };
    
    SDL_Rect floor
    {
        0,
        768-thickness,
        1024,
        thickness
    };
    
    SDL_Rect leftWall
    {
        0,
        0,
        thickness,
        768
    };
    
    SDL_Rect rightWall
    {
        1024-thickness,
        0,
        thickness,
        768
    };
    
    SDL_Rect ball
    {
        static_cast<int>(mBallPosition.x - thickness/2),
        static_cast<int>(mBallPosition.y - thickness/2),
        thickness,
        thickness
    };
    
    SDL_Rect leftPaddle
    {
        static_cast<int>(mLeftPaddlePosition.x - thickness/2),
        static_cast<int>(mLeftPaddlePosition.y - thickness/2 - mPaddleLength/2),
        thickness,
        mPaddleLength
    };
    
    SDL_Rect rightPaddle
    {
        static_cast<int>(mRightPaddlePosition.x - thickness/2),
        static_cast<int>(mRightPaddlePosition.y - thickness/2 - mPaddleLength/2),
        thickness,
        mPaddleLength
    };
    
    SDL_RenderFillRect(mRenderer, &ceiling);
    SDL_RenderFillRect(mRenderer, &floor);
    SDL_RenderFillRect(mRenderer, &leftWall);
    SDL_RenderFillRect(mRenderer, &rightWall);
    
    SDL_RenderFillRect(mRenderer, &ball);
    SDL_RenderFillRect(mRenderer, &leftPaddle);
    SDL_RenderFillRect(mRenderer, &rightPaddle);
    
    // Swap the buffers
    SDL_RenderPresent(mRenderer);
}

void Game::UpdateGame()
{
    
}


