#include "gamedata.hpp"
#include "viewer.hpp"
#include "raylib.h"

Viewer::Viewer()
{
    InitWindow(800, 450, "raylib [core] example - basic window");
}

void Viewer::draw(Gamedata& gamedata)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
}