#include "raylib.h"
#include "engine.hpp"
#include "gamedata.hpp"
#include "viewer.hpp"
#include "controller.hpp"

int main() {
    Controller* controller = new Controller();
    Viewer* viewer = new Viewer();
    Gamedata* gamedata = new Gamedata("test_map.scpac");

    Engine* engine = Engine::get_instance(controller, gamedata, viewer);

    engine->run();

    return 0;
}