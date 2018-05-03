#pragma once

#include <SDL2/SDL.h>

#include "../Video.hpp"

namespace Engine
{

namespace GUI
{

struct Rectangle
{
    Rectangle( Renderer& ren
             , const float position_x
             , const float position_y
             , const float size_x
             , const float size_y
             , const SDL_Color color
             );
    ~Rectangle();
    
    void draw() const;
    
    Renderer& renderer;
    
    const float pos_x = 0.0f;
    const float pos_y = 0.0f;
    const float width = 0.0f;
    const float height = 0.0f;
    
    Texture* tex = nullptr;
};

}

}
