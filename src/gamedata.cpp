#include "gamedata.hpp"
#include "entity/entity.hpp"
#include "entity/orb.hpp"
#include "entity/player.hpp"
#include "entity/scp_939.hpp"
#include "events.hpp"

#include <fstream>
#include <vector>
Gamedata::Gamedata(std::string filename)
{
    std::string filepath = "resources/maps/" + filename;
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
                player_ = new ent::Player(i + 0.5, j + 0.5);
                break;
            case 'E':
                enemies_.push_back(new ent::SCP_939(i + 0.5, j + 0.5));
                break;
            case '.':
                orbs_.push_back(new ent::Orb(i + 0.5, j + 0.5));
                break;
            default:
                throw std::runtime_error("Unknown map symbol\n");
                break;
            }
        }
    }
}

// Методы Gamedata
std::vector<std::vector<Tile>> Gamedata::get_map() { return tiles_; }

std::vector<ent::Entity *> Gamedata::get_enemies() { return enemies_; }

ent::Player *Gamedata::get_player() { return player_; }

std::vector<ent::Orb *> Gamedata::get_orbs() { return orbs_; }

void Gamedata::update_event(Event event, bool event_value)
{
    if (static_cast<std::size_t>(event) < 4)
    {
        last_pressed_direction_ = event;
    }
    events_[static_cast<std::size_t>(event)] = event_value;
}

void Gamedata::update_mouse(int mouse_x, int mouse_y, bool is_mouse_pressed, bool is_mouse_down, bool is_mouse_released, bool is_mouse_up)
{
    mouse_x_ = mouse_x;
    mouse_y_ = mouse_y;
    is_mouse_pressed_ = is_mouse_pressed;
    is_mouse_down_ = is_mouse_down;
    is_mouse_released_ = is_mouse_released;
    is_mouse_up_ = is_mouse_up;
}

void Gamedata::step() {}

Gamedata::~Gamedata()
{
    for (ent::Orb *orb : orbs_)
        delete orb;

    delete player_;

    for (ent::Entity *enemy : enemies_)
        delete enemy;
}