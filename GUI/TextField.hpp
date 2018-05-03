#pragma once

#include "../Video.hpp"

#include "Rectangle.hpp"
#include "TextLayer.hpp"

namespace Engine
{

struct TextField
{
    TextField( Renderer& renderer
             , const std::string text
             , const float position_x
             , const float position_y
             , const float size_x
             , const float size_y
             , const SDL_Color background_color = { 0x13
                                                  , 0x13
                                                  , 0x13
                                                  , 0xFF
                                                  }
             , const SDL_Color text_color = { 0xFF
                                            , 0xFF
                                            , 0xFF
                                            , 0xFF
                                            }
             );
    ~TextField();
    
    void draw() const;
    
    const GUI::Rectangle background;
    const GUI::TextLayer text;
};

}
