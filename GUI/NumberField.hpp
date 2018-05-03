#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../Font.hpp"
#include "../Video.hpp"

#include "Rectangle.hpp"
#include "TextLayer.hpp"

namespace Engine
{

struct NumberField
{
    NumberField( Renderer& ren
               , float position_x = 0.5f
               , float position_y = 0.05f
               , float size_x     = 0.1f
               , float size_y     = 0.1f
               , SDL_Color background_color = { 0x13
                                              , 0x13
                                              , 0x13
                                              , 0xFF
                                              }
               , SDL_Color text_color = { 0xFF
                                        , 0xFF
                                        , 0xFF
                                        , 0xFF
                                        }
               );
    ~NumberField();
    
    // num is in range 0...9
    void showNumber( int num );
    
    void draw() const;
    
    const GUI::TextLayer numbers[10];

    const GUI::Rectangle background;
    
    int current_number = 0;
};

}
