#include "engine.hpp"
#include "raylib.h"

Engine* Engine::engine_= nullptr;

void Engine::run(){
    while(!WindowShouldClose()){
        controller_->update_input(gamedata_);
        gamedata_->step();
        viewer_->draw(gamedata_);
    }

    CloseWindow();

    delete this;
}

Engine::~Engine(){
    delete controller_;
    delete gamedata_;
    delete viewer_;
}
