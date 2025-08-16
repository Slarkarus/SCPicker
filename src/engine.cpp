#include "engine.hpp"
#include "raylib.h"

Engine* Engine::engine_= nullptr;

void Engine::wait_for_step(){
    
}

void Engine::run(){
    while(!WindowShouldClose()){
        (*controller_).update_input(gamedata_);
        gamedata_.step();
        (*viewer_).draw(gamedata_);
        wait_for_step();
    }

    CloseWindow();
}