//
//  Game.h
//  SDL Pong
//
//  Created by Alex Donisthorpe on 08/05/2021.
//

#ifndef Game_h
#define Game_h

#include "SDL2.framework/Headers/SDL.h"

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
};


#endif /* Game_h */
