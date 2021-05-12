//
//  Game.h
//  SDL Pong
//
//  Created by Alex Donisthorpe on 08/05/2021.
//

#ifndef Game_h
#define Game_h

#include "SDL2.framework/Headers/SDL.h"
#include <vector>

struct Vector2
{
    float x;
    float y;
};

struct Ball
{
    Vector2 position;
    Vector2 velocity;
    
    void Init(float xPosition, float yPosition, float xVelocity, float yVelocity)
    {
        position.x = xPosition;
        position.y = yPosition;
        velocity.x = xVelocity;
        velocity.y = yVelocity;
    }
};

class Game
{
public:
    Game();
    
    bool Initialize();
    void RunLoop();
    void Shutdown();
private:
    void ProcessInput();
    void extracted(Ball &ball, float deltaTime);
    
    void UpdateGame();
    void GenerateOutput();
    void MovePaddle(Vector2 &paddlePosition, int &paddleDirection, float deltaTime);
    void MoveBall(Ball &ball, float deltaTime);
    
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    
    bool mIsRunning = true;
    
    const int mPaddleLength = 100;
    const int thickness = 15;
    int mLeftPaddleDirection;
    int mRightPaddleDirection;
    
    Uint32 mTicksCount;
    
    std::vector<Ball> mBallsInPlay;
    
    Ball mBall1, mBall2, mBall3;
    
    Vector2 mLeftPaddlePosition;
    Vector2 mRightPaddlePosition;
};


#endif /* Game_h */
