#ifndef ENTITY_ENTITY_HPP
#define ENTITY_ENTITY_HPP

#include "gamedata.hpp"
#include <utility>
#include <cmath>

namespace ent
{
    class Entity
    {
    protected:
        double x_pos_;
        double y_pos_;
        Direction direction_;

    public:
        virtual ~Entity() = default;

        std::pair<double, double> get_pos();

        Direction get_direction() { return direction_; }

        virtual void step(Gamedata *gamedata) = 0;

        Entity(double x_pos, double y_pos, Direction direction = Direction::Right) : x_pos_(x_pos), y_pos_(y_pos), direction_(direction) {}

        template <typename T>
        T *get_collide_entity(std::vector<T *> entities);

        void set_pos(double x_pos, double y_pos);

        void set_pos(std::pair<double, double> pos);
    };
};

template <typename T>
T *ent::Entity::get_collide_entity(std::vector<T *> entities)
{
    for (T *entity : entities)
    {
        auto pos = entity->get_pos();

        if (fabs(pos.first - x_pos_) < 0.5 && fabs(pos.second - y_pos_) < 0.5)
        {
            return entity;
        }
    }
    return nullptr;
}

#endif // ENTITY_ENTITY_HPP
