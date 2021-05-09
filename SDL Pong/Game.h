//
//  Game.h
//  SDL Pong
//
//  Created by Alex Donisthorpe on 08/05/2021.
//

#ifndef Game_h
#define Game_h

#include "SDL2.framework/Headers/SDL.h"

struct Vector2
{
    float x;
    float y;
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
    void UpdateGame();
    void GenerateOutput();
    
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    
    bool mIsRunning = true;
    
    const int mPaddleLength = 100;
    const int thickness = 15;
    
    Vector2 mBallPosition;
    Vector2 mLeftPaddlePosition;
    Vector2 mRightPaddlePosition;
};


#endif /* Game_h */
