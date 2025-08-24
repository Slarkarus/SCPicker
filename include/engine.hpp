#include "gamedata.hpp"
#include "controller.hpp"
#include "viewer.hpp"
#include "constants.hpp"

#ifndef ENGINE_HPP
#define ENGINE_HPP

enum class Scene
{
    Menu,
    Game,
    Settings,
    Win,
    Lose,
};

class Engine
{
private:
    Controller *controller_;

    Gamedata *gamedata_;
    
    Viewer *viewer_;
    
    Scene current_scene_;

    Engine(Controller *controller, Gamedata *gamedata, Viewer *viewer) : controller_(controller), gamedata_(gamedata), viewer_(viewer), current_scene_(Scene::Menu)
    {
        SetTargetFPS(FPS);
    }

    static Engine *engine_;

public:
    Engine(Engine &other) = delete;

    void operator=(const Engine &) = delete;

    static Engine *get_instance(Controller *controller, Gamedata *gamedata, Viewer *viewer)
    {
        if (engine_ == nullptr)
        {
            engine_ = new Engine(controller, gamedata, viewer);
        }
        return engine_;
    }

    void run();

    ~Engine();
};

#endif
