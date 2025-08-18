#include "gamedata.hpp"
#include "viewer.hpp"
#include "raylib.h"

Viewer::Viewer()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Делаем окно изменяемого размера
    SetConfigFlags(FLAG_WINDOW_MAXIMIZED); // Разрешаем использовать квадратик в правом верхнем углу

    InitWindow(800, 450, "SCP game");
    MaximizeWindow();

    load_textures();
}

Viewer::~Viewer()
{
    for (auto &texture : textures_map_)
    {
        UnloadTexture(texture.second);
    }
}

void Viewer::load_textures()
{
    textures_map_["exit"] = LoadTexture("resources/images/exit.png");
    textures_map_["floor"] = LoadTexture("resources/images/floor.png");
    textures_map_["wall"] = LoadTexture("resources/images/wall.png");
}

void Viewer::draw(Gamedata *gamedata)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    std::vector<std::vector<Tile>> field = gamedata->get_map();

    float field_width = field[0].size();
    float field_height = field.size();

    float tile_width_perc = 0.9f / field_width;
    float tile_height_perc = 0.9f / field_height;
    float tile_width_pixels = tile_width_perc * screen_width;
    float tile_height_pixels = tile_height_perc * screen_height;

    float tile_side_pixels;
    if (tile_width_pixels <= tile_height_pixels)
    {
        tile_side_pixels = tile_width_pixels;
        tile_height_perc = tile_side_pixels / screen_height;
    }
    else
    {
        tile_side_pixels = tile_height_pixels;
        tile_width_perc = tile_side_pixels / screen_width;
    }

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

            float x_percents = 0.05f + pos_x * tile_width_perc;
            float y_percents = 0.05f + pos_y * tile_height_perc;

            Rectangle dest = {screen_width * x_percents, screen_height * y_percents, tile_side_pixels, tile_side_pixels};
            Rectangle src = {0, 0, (float)tile_texture.width, (float)tile_texture.height};
            Vector2 rotate = {0, 0};
            DrawTexturePro(tile_texture, src, dest, rotate, 0.0f, WHITE);
        }
    }
    // ClearBackground(RAYWHITE);
    // DrawText("Congrats! You created your first resizable window!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
}