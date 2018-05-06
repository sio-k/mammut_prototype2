/*
    Mammut game prototype, version 2.
    Copyright (C) 2018 Sio Kreuzer

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
