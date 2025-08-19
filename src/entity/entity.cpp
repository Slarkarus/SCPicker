#include "gamedata.hpp"
#include "entity/entity.hpp"

std::pair<double, double> ent::Entity::get_pos() { return {x_pos_, y_pos_}; }
void ent::Entity::step(Gamedata &gamedata) {}

