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
