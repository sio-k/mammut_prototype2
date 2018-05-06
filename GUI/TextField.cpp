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
#include "TextField.hpp"

using namespace Engine;

TextField::TextField( Renderer& renderer
                    , const std::string text
                    , const float position_x
                    , const float position_y
                    , const float size_x
                    , const float size_y
                    , const SDL_Color background_color
                    , const SDL_Color text_color
                    )
    : background( renderer 
                , position_x
                , position_y
                , size_x
                , size_y
                , background_color
                )
    , text( renderer 
          , text
          , position_x
          , position_y
          , size_x
          , size_y
          , text_color
          )
{
}

TextField::~TextField()
{
}

void TextField::draw() const
{
    background.draw();
    text.draw();
}
