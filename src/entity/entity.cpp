#include "gamedata.hpp"
#include "entity/entity.hpp"
#include <cmath>

std::pair<double, double> ent::Entity::get_pos() { return {x_pos_, y_pos_}; }

void ent::Entity::set_pos(double x_pos, double y_pos){
    x_pos_ = x_pos;
    y_pos_ = y_pos;
}

void ent::Entity::set_pos(std::pair<double, double> pos){
    x_pos_ = pos.first;
    y_pos_ = pos.second;
}