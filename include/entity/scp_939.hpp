#ifndef ENTITY_SCP_939_HPP
#define ENTITY_SCP_939_HPP

#include "gamedata.hpp"
#include "entity/entity.hpp"

namespace ent
{
    class SCP_939 : public Entity
    {
    public:
        using Entity::Entity;

        void step(Gamedata *gamedata);
    };
};

#endif // ENTITY_SCP_939_HPP
