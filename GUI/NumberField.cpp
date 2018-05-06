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
#include "NumberField.hpp"

#include <assert.h>

using namespace Engine;
using namespace GUI;

NumberField::NumberField( Renderer& ren
                        , float position_x
                        , float position_y
                        , float size_x
                        , float size_y
                        , SDL_Color background_color
                        , SDL_Color text_color
                        )
    : numbers { TextLayer( ren
                         , "0"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "1"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "2"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "3"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "4"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "5"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "6"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "7"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "8"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "9"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              }
    , background( ren
                , position_x
                , position_y
                , size_x
                , size_y
                , background_color
                )
    , current_number( 0 )
{
}

NumberField::~NumberField()
{
}

void NumberField::showNumber( int num )
{
    current_number = num >= 0 && num <= 9 ? num : 0;
}

void NumberField::draw() const
{
    background.draw();
    numbers[current_number].draw();
}
