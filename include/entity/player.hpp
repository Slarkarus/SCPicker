#ifndef ENTITY_PLAYER_HPP
#define ENTITY_PLAYER_HPP

#include "gamedata.hpp"
#include "entity/entity.hpp"
#include <vector>

namespace ent
{
    class Player : public Entity
    {
    public:
        using Entity::Entity;

        void step(Gamedata *gamedata);
    };
};

#endif // ENTITY_PLAYER_HPP
