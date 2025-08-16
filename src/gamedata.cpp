#include "gamedata.hpp"
#include <fstream>
#include <iostream>
#include <vector>

Gamedata::Gamedata(std::string filename)
{
    std::string filepath = "resources/maps/" +  filename;
    std::ifstream fin(filepath);
    if (!fin)
        throw std::runtime_error("Unable to open " + filepath);

    int height, width;
    fin >> height >> width;

    if (width <= 0 || height <= 0)
    {
        throw std::runtime_error("Invalid map size");
    }
    tiles_.resize(height, std::vector<Tile>(width, Tile::Empty));

    char tile_char;
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            fin >> tile_char;
            std::cout << tile_char;
            switch (tile_char)
            {
            case '#':
                tiles_[i][j] = Tile::Wall;
                break;
            case '_':
                break;
            case 'X':
                tiles_[i][j] = Tile::Exit;
                break;
            case 'P':
                player_ = new Player(i + 0.5, j + 0.5);
                break;
            case 'E':
                enemies_.push_back(SCP_939(i+0.5, j+0.5));
                break;
            case '.':
                orbs_.push_back(Orb(i+0.5, j+0.5));
                break;
            default:
                throw std::runtime_error("Unknown map symbol\n");
                break;
            }
        }
        std::cout << '\n';
    }
}

// Методы Entity
std::pair<double, double> Entity::get_pos() { return {x_pos_, y_pos_}; }
void Entity::step(Gamedata &gamedata) {}

// Методы наследников
void SCP_939::step(Gamedata &gamedata) {}
void Player::step(Gamedata &gamedata) {}
void Orb::step(Gamedata &gamedata) {}

// Методы Gamedata
std::vector<std::vector<Tile>> Gamedata::get_map() { return tiles_; }
std::vector<Entity> Gamedata::get_enemies() { return enemies_; }
Player Gamedata::get_player() { return *player_; }
std::vector<Orb> Gamedata::get_orbs() { return orbs_; }
void Gamedata::update_input(std::string input_name, bool input_value) { input_[input_name] = input_value; }
void Gamedata::step() {}