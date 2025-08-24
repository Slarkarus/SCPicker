#include <gamedata.hpp>
#include <map>
#include "raylib.h"

#ifndef VIEWER_HPP
#define VIEWER_HPP

class Viewer
{
private:
    float tile_side_pixels_;
    std::map<std::string, Texture2D> textures_map_;

    void load_textures_();

    void calculate_tile_side_(const std::vector<std::vector<Tile>> &field);

    std::pair<float, float> get_pixel_pos_(float tile_pos_x, float tile_pos_y);

    void draw_element_(float tile_pos_x, float tile_pos_y, Texture2D texture);
    
    void draw_field_(const std::vector<std::vector<Tile>> &field);

    void draw_entities_(const std::vector<ent::Entity *> &enemies, ent::Player *player,
                       const std::vector<ent::Orb *> &orbs);

public:
    void draw(Gamedata *gamedata);

    Viewer();

    ~Viewer();
};

#endif