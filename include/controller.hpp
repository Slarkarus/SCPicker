#include "gamedata.hpp"
#include <map>

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller
{

private:
    std::map<std::string, bool> input_;

    std::map<std::string, bool> last_input_;

public:
    void update_input(Gamedata *game_data);

    Controller();
};

#endif