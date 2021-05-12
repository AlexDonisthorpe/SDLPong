//
//  Game.cpp
//  SDL Pong
//
//  Created by Alex Donisthorpe on 08/05/2021.
//

#include <stdio.h>
#include "Game.h"

Game::Game()
    :mWindow(nullptr)
    ,mRenderer(nullptr)
    ,mTicksCount(0)
    ,mIsRunning(true)
    ,mLeftPaddleDirection(0)
    ,mRightPaddleDirection(0)
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
    
    // Set Paddle Starting Positions
    mLeftPaddlePosition.x = 30;
    mLeftPaddlePosition.y = 384;
    
    mRightPaddlePosition.x = 1024 - 30;
    mRightPaddlePosition.y = 384;
    
    mBall1.Init(512, 384, -200.0f, 235.0f);
    mBall2.Init(512, 200, 200.0f, -235.0f);
    mBall3.Init(512, 640, -300.0f, 150.0f);
    
    mBallsInPlay.push_back(mBall1);
    mBallsInPlay.push_back(mBall2);
    mBallsInPlay.push_back(mBall3);
    
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
    
    // Left Paddle input
    mLeftPaddleDirection = 0;
    if(KeyboardState[SDL_SCANCODE_W])
    {
        // negative y
        mLeftPaddleDirection -= 1;
    }
    
    if(KeyboardState[SDL_SCANCODE_S])
    {
        mLeftPaddleDirection += 1;
    }
    
    // Right Paddle input
    mRightPaddleDirection = 0;
    if(KeyboardState[SDL_SCANCODE_UP])
    {
        // negative y
        mRightPaddleDirection -= 1;
    }
    if(KeyboardState[SDL_SCANCODE_DOWN])
    {
        mRightPaddleDirection += 1;
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
    
    SDL_Rect Balls[mBallsInPlay.size()];
    
    for(int i = 0; i < mBallsInPlay.size(); i++)
    {
        Balls[i].x = static_cast<int>(mBallsInPlay[i].position.x - thickness/2);
        Balls[i].y = static_cast<int>(mBallsInPlay[i].position.y - thickness/2);
        Balls[i].h = thickness;
        Balls[i].w = thickness;
        SDL_RenderFillRect(mRenderer, &Balls[i]);
        
    }
    
    SDL_RenderFillRect(mRenderer, &ceiling);
    SDL_RenderFillRect(mRenderer, &floor);
    SDL_RenderFillRect(mRenderer, &leftWall);
    SDL_RenderFillRect(mRenderer, &rightWall);
    
    
    SDL_RenderFillRect(mRenderer, &leftPaddle);
    SDL_RenderFillRect(mRenderer, &rightPaddle);
    
    // Swap the buffers
    SDL_RenderPresent(mRenderer);
    
}

void Game::MoveBall(Ball &ball, float deltaTime) {
    ball.position.x += ball.velocity.x * deltaTime;
    ball.position.y += ball.velocity.y * deltaTime;
    
    
    // Check if ball is hitting the roof
    if(ball.position.y <= thickness && ball.velocity.y < 0.0f)
    {
        ball.velocity.y *= -1;
    }
    
    // Check if the ball is hitting the floor
    if(ball.position.y >= 768-thickness && ball.velocity.y > 0.0f)
    {
        ball.velocity.y *= -1;
    }
    
    // Check Left Wall
    if(ball.position.x <= thickness && ball.velocity.x < 0.0f)
    {
        ball.velocity.x *= -1;
    }
    
    // Check Right Wall
    if(ball.position.x >= 1024-thickness && ball.velocity.x > 0.0f)
    {
        ball.velocity.x *= -1;
    }
    
    // Check ball left paddle
    if(ball.position.x < mLeftPaddlePosition.x + thickness/2 &&
       ball.position.x > mLeftPaddlePosition.x - thickness/2)
    {
        if(ball.position.y >= mLeftPaddlePosition.y - mPaddleLength/2 &&
           ball.position.y <= mLeftPaddlePosition.y + mPaddleLength/2){
            ball.velocity.x *= -1;
        }
    }
    
    // Check ball right paddle
    if(ball.position.x < mRightPaddlePosition.x + thickness/2 &&
       ball.position.x > mRightPaddlePosition.x - thickness/2)
    {
        if(ball.position.y >= mRightPaddlePosition.y - mPaddleLength/2 &&
           ball.position.y <= mRightPaddlePosition.y + mPaddleLength/2){
            ball.velocity.x *= -1;
        }
    }
}

void Game::UpdateGame()
{
    // Waiting to ensure maximum frame-rate is 60fps
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    
    // deltaTime in seconds
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    
    // Clamping deltaTime
    if(deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    
    MovePaddle(mLeftPaddlePosition, mLeftPaddleDirection, deltaTime);
    MovePaddle(mRightPaddlePosition, mRightPaddleDirection, deltaTime);
    
    for(int i = 0; i < mBallsInPlay.size(); i++)
    {
        MoveBall(mBallsInPlay[i], deltaTime);
    }
    
    
    mTicksCount = SDL_GetTicks();
}

void Game::MovePaddle(Vector2 &paddlePosition, int &paddleDirection, float deltaTime)
{
    if(paddleDirection != 0)
    {
        paddlePosition.y += paddleDirection * 300.0f * deltaTime;
    }
    
    if(paddlePosition.y < (mPaddleLength / 2.0f + 2 * thickness))
    {
        paddlePosition.y = mPaddleLength/2.0f + 2 * thickness;
    } else if(paddlePosition.y > (768.0f - mPaddleLength/2.0f - thickness))
    {
        paddlePosition.y = (768.0f - mPaddleLength/2.0f - thickness);
    }
}

