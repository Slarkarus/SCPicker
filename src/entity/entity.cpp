#include "gamedata.hpp"
#include "entity/entity.hpp"
#include <cmath>

std::pair<double, double> ent::Entity::get_pos() { return {x_pos_, y_pos_}; }

ent::Entity *ent::Entity::get_collide_entity(std::vector<ent::Entity *> entities)
{
    for (ent::Entity *entity : entities)
    {
        auto pos = entity->get_pos();

        if (fabs(pos.first - x_pos_) < 0.5 && fabs(pos.second - y_pos_) < 0.5)
        {
            return entity;
        }
    }
    return nullptr;
}



