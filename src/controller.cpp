#include "controller.hpp"
#include "gamedata.hpp"
#include "events.hpp"
#include "raylib.h"

Controller::Controller() {}

template <Event e, KeyboardKey k> 
inline void update_custom_gamedata_event(Gamedata *gamedata){
    if(IsKeyDown(k)){
        gamedata->update_event(e, true);
    }
    else{
        gamedata->update_event(e, false);
    }
}

void Controller::update_input(Gamedata *gamedata)
{
    update_custom_gamedata_event<Event::Left, KEY_A>(gamedata);
    update_custom_gamedata_event<Event::Right, KEY_D>(gamedata);
    update_custom_gamedata_event<Event::Up, KEY_W>(gamedata);
    update_custom_gamedata_event<Event::Down, KEY_S>(gamedata);
    update_custom_gamedata_event<Event::Enter, KEY_ENTER>(gamedata);
    update_custom_gamedata_event<Event::Space, KEY_SPACE>(gamedata);
    update_custom_gamedata_event<Event::Escape, KEY_ESCAPE>(gamedata);

    gamedata->update_mouse(GetMouseX(), GetMouseY(), IsMouseButtonPressed(0), IsMouseButtonDown(0), IsMouseButtonReleased(0), IsMouseButtonUp(0));
}
