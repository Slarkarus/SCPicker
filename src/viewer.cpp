#include "entity/entity.hpp"
#include "gamedata.hpp"
#include "viewer.hpp"
#include "raylib.h"

Viewer::Viewer()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Делаем окно изменяемого размера
    SetConfigFlags(FLAG_WINDOW_MAXIMIZED); // Разрешаем использовать квадратик в правом верхнем углу

    InitWindow(800, 450, "SCP game");
    MaximizeWindow();

    load_textures_();
}

Viewer::~Viewer()
{
    for (auto &texture : textures_map_)
    {
        UnloadTexture(texture.second);
    }
}

void Viewer::load_textures_()
{
    textures_map_["exit"] = LoadTexture("resources/images/exit.png");
    textures_map_["floor"] = LoadTexture("resources/images/floor.png");
    textures_map_["wall"] = LoadTexture("resources/images/wall.png");
    textures_map_["player"] = LoadTexture("resources/images/player.png");
    textures_map_["orb"] = LoadTexture("resources/images/orb.png");
    textures_map_["scp_939"] = LoadTexture("resources/images/scp_939.png");
}

void Viewer::calculate_tile_side_(const std::vector<std::vector<Tile>> &field)
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    float field_width = field[0].size();
    float field_height = field.size();

    float tile_width_perc = 0.9f / field_width;
    float tile_height_perc = 0.9f / field_height;
    float tile_width_pixels = tile_width_perc * screen_width;
    float tile_height_pixels = tile_height_perc * screen_height;

    tile_side_pixels_ = std::min(tile_width_pixels, tile_height_pixels);
}

std::pair<float, float> Viewer::get_pixel_pos_(float tile_pos_x, float tile_pos_y)
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    float tile_width_perc = tile_side_pixels_ / screen_width;
    float tile_height_perc = tile_side_pixels_ / screen_height;

    float x_percents = 0.05f + tile_pos_x * tile_width_perc;
    float y_percents = 0.05f + tile_pos_y * tile_height_perc;
    return {screen_width * x_percents, screen_height * y_percents};
}

void Viewer::draw_element_(float tile_pos_x, float tile_pos_y, Texture2D texture) {
    std::pair<float, float> pixel_coords = get_pixel_pos_(tile_pos_x, tile_pos_y);
    Rectangle dest = {pixel_coords.first, pixel_coords.second, tile_side_pixels_, tile_side_pixels_};
    Rectangle src = {0, 0, (float)texture.width, (float)texture.height};
    Vector2 rotate = {0, 0};
    DrawTexturePro(texture, src, dest, rotate, 0.0f, WHITE);
}

void Viewer::draw_field_(const std::vector<std::vector<Tile>> &field)
{
    float field_width = field[0].size();
    float field_height = field.size();

    Tile tile;
    for (size_t pos_y = 0; pos_y < field_height; pos_y++)
    {
        for (size_t pos_x = 0; pos_x < field_width; pos_x++)
        {
            Texture2D tile_texture;
            switch (field[pos_y][pos_x])
            {
            case Tile::Empty:
                tile_texture = textures_map_["floor"];
                break;

            case Tile::Wall:
                tile_texture = textures_map_["wall"];
                break;

            case Tile::Exit:
                tile_texture = textures_map_["exit"];
                break;
            }

            draw_element_(pos_x, pos_y, tile_texture);
        }
    }
}

void Viewer::draw_entities_(const std::vector<ent::Entity *> &enemies, ent::Player *player,
                           const std::vector<ent::Orb *> &orbs)
{
    
}

void Viewer::draw(Gamedata *gamedata)
{
    calculate_tile_side_(gamedata->get_map());

    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_field_(gamedata->get_map());
    draw_entities_(gamedata->get_enemies(), gamedata->get_player(), gamedata->get_orbs());

    EndDrawing();
}