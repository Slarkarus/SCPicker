#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "gamedata.hpp"
#include "events.hpp"
#include <map>

class Controller
{
private:
public:
    void update_input(Gamedata *game_data);

    Controller();
};

#endif // CONTROLLER_HPP
