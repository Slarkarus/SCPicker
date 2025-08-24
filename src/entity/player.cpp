#include "gamedata.hpp"
#include "entity/player.hpp"
#include "entity/orb.hpp"
#include "constants.hpp"
#include "events.hpp"

#include <iostream>
#include <cmath>
#include <cstdlib>

bool is_win = false; // TODO: Burn That WIth Fire

void ent::Player::step(Gamedata *gamedata)
{
    std::pair<int, int> preferred_tile;
    std::pair<int, int> current_tile = {floor(x_pos_), floor(y_pos_)};
    Direction preferred_direction = static_cast<Direction>(gamedata->get_last_pressed_direction());
    switch (preferred_direction) {
        case Direction::Up:
            preferred_tile = {current_tile.first, current_tile.second - 1}; 
            break;
        case Direction::Right:
            preferred_tile = {current_tile.first + 1, current_tile.second}; 
            break;
        case Direction::Left:
            preferred_tile = {current_tile.first - 1, current_tile.second}; 
            break;
        case Direction::Down:
            preferred_tile = {current_tile.first, current_tile.second + 1}; 
            break;
    }
    
    std::vector<std::vector<Tile>> field = gamedata->get_map();
     
    if (field[preferred_tile.second][preferred_tile.first] != Tile::Wall &&
        fabs(x_pos_ - floor(x_pos_) - 0.5) < DOUBLE_EPS && fabs(y_pos_ - floor(y_pos_) - 0.5) < DOUBLE_EPS) {
        direction_ = preferred_direction;
    }

    switch (direction_) {
        case Direction::Up:
            if (field[current_tile.second - 1][current_tile.first] != Tile::Wall ||
                (y_pos_ - floor(y_pos_)) > 0.5 + DOUBLE_EPS) {
                y_pos_ -= PLAYER_SPEED;
            }
            break;
        case Direction::Right:
            if (field[current_tile.second][current_tile.first + 1] != Tile::Wall ||
                (x_pos_ - floor(x_pos_)) < 0.5 - DOUBLE_EPS) {
                x_pos_ += PLAYER_SPEED;
            }
            break;
        case Direction::Left:
            if (field[current_tile.second][current_tile.first - 1] != Tile::Wall ||
                (x_pos_ - floor(x_pos_)) > 0.5 + DOUBLE_EPS) {
                x_pos_ -= PLAYER_SPEED;
            }
            break;
        case Direction::Down:
            if (field[current_tile.second + 1][current_tile.first] != Tile::Wall ||
                (y_pos_ - floor(y_pos_)) < 0.5 - DOUBLE_EPS) {
                y_pos_ += PLAYER_SPEED;
            }
            break;
    }

    std::vector<ent::Orb *>& orbs = gamedata->get_orbs();
    ent::Orb* collided_orb = get_collide_entity(orbs);
    if (collided_orb) {
        orbs.erase(std::remove(orbs.begin(), orbs.end(), collided_orb), orbs.end());
    }

    std::vector<ent::Entity *>& enemies = gamedata->get_enemies();
    ent::Entity* collided_enemy = get_collide_entity(enemies);
    if (collided_enemy) {
        x_pos_ = 10000;
    }

    if (orbs.empty() && field[current_tile.second][current_tile.first] == Tile::Exit) {
        is_win = true;
    }

    if (is_win) {
        x_pos_ = 1 + std::rand() % (field[0].size() - 2);
        y_pos_ = 1 + std::rand() % (field.size() - 2);
    }
}