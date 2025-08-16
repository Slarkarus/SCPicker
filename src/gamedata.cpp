#include "gamedata.hpp"

Gamedata::Gamedata() : player(0,0) {}

// Методы Entity
std::pair<double,double> Entity::get_pos(){ return {x_pos_, y_pos_}; }
void Entity::step(Gamedata &gamedata){}

// Методы наследников
void SCP_939::step(Gamedata &gamedata){}
void Player::step(Gamedata &gamedata){}
void Orb::step(Gamedata &gamedata){}

// Методы Gamedata
std::vector<std::vector<Tile>> Gamedata::get_map(){ return tiles; }
std::vector<Entity> Gamedata::get_enemies(){ return enemies; }
Player Gamedata::get_player(){ return player; }
std::vector<Orb> Gamedata::get_orbs(){ return orbs; }
void Gamedata::update_input(std::string input_name, bool input_value){ input[input_name]=input_value; }
void Gamedata::step(){}