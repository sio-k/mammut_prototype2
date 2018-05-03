#pragma once

#include <SDL2/SDL.h>

#include <string>

#include "../Video.hpp"
#include "../Font.hpp"

namespace Engine
{

namespace GUI
{

struct TextLayer
{
    TextLayer( Renderer& ren 
             , const std::string text
             , const float position_x
             , const float position_y
             , const float size_x
             , const float size_y
             , const SDL_Color text_color
             );
    ~TextLayer();
    
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
