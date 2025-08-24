#ifndef ENTITY_SCP_939_HPP
#define ENTITY_SCP_939_HPP

#include "gamedata.hpp"
#include "entity/entity.hpp"
#include <vector>
#include <utility>

namespace ent
{
    class SCP_939 : public Entity
    {        
    public:
        std::vector <std::pair<double, double>> next_path_; 
        
        using Entity::Entity;

        void step(Gamedata *gamedata);

    };
};

#endif // ENTITY_SCP_939_HPP
