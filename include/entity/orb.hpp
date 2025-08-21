#ifndef ENTITY_ORB_HPP
#define ENTITY_ORB_HPP

#include "gamedata.hpp"
#include "entity/entity.hpp"

namespace ent
{
    class Orb : public Entity
    {
    private:
        bool is_collected = false;

    public:
        using Entity::Entity;

        void step(Gamedata *gamedata);
    };
};

#endif // ENTITY_ORB_HPP
