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
#include "../Video.hpp"

using namespace Engine;

RenderPosition::RenderPosition( Renderer& renderer
                              , float normalized_x
                              , float normalized_y
                              , float normalized_w
                              , float normalized_h
                              , float depth
                              )
    : sdl { ( int ) ( ( float ) renderer.width()  * normalized_x )
          , ( int ) ( ( float ) renderer.height() * normalized_y )
          , ( int ) ( ( float ) renderer.width()  * normalized_w )
          , ( int ) ( ( float ) renderer.height() * normalized_h )
          }
    , gl( ( GLfloat ) normalized_x
        , ( GLfloat ) normalized_y
        , ( GLfloat ) normalized_w
        , ( GLfloat ) normalized_h
        , ( GLfloat ) depth
        )
{
}
