#ifndef ENTITY_ENTITY_HPP
#define ENTITY_ENTITY_HPP

#include "gamedata.hpp"
#include <utility>

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

        virtual void step(Gamedata &gamedata);

        Entity(double x_pos, double y_pos, Direction direction = Direction::Right) : x_pos_(x_pos), y_pos_(y_pos), direction_(direction) {}
    };
};

#endif // ENTITY_ENTITY_HPP
