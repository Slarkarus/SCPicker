#include <gamedata.hpp>
#include <map>
#include "raylib.h"

#ifndef VIEWER_HPP
#define VIEWER_HPP

class Viewer
{
private:
    std::map<std::string, Texture2D> textures_map_;
    void load_textures();

public:
    void draw(Gamedata *gamedata);

    Viewer();
    
    ~Viewer();
};

#endif