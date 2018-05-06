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
#include "Rectangle.hpp"

#include "../let.hpp"

#include <assert.h>

using namespace Engine;
using namespace GUI;

Rectangle::Rectangle( Renderer& ren
                    , const float position_x
                    , const float position_y
                    , const float size_x
                    , const float size_y
                    , const SDL_Color color
                    )
    : renderer( ren )
    , pos_x( position_x )
    , pos_y( position_y )
    , width( size_x )
    , height( size_y )
    , tex( nullptr )
{
    uint32_t rmask = 0;
    uint32_t gmask = 0;
    uint32_t bmask = 0;
    uint32_t amask = 0;
    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif
    
    let* surface = SDL_CreateRGBSurface( 0
                                       , 1280
                                       , 720
                                       , 32
                                       , rmask
                                       , gmask
                                       , bmask
                                       , amask
                                       );
    assert( surface != nullptr );
    SDL_FillRect( surface
                , nullptr
                , SDL_MapRGBA( surface -> format
                             , color.r
                             , color.g
                             , color.b
                             , color.a
                             )
                );
    
    tex = ren.getTextureFromSurface( surface );
    assert( tex != nullptr );
    
    SDL_FreeSurface( surface );
    surface = nullptr;
}

Rectangle::~Rectangle()
{
    // we let the texture get freed by the renderer
}

void Rectangle::draw() const
{
    renderer.render( tex
                   , RenderPosition( renderer
                                   , pos_x
                                   , pos_y
                                   , width
                                   , height
                                   )
                   );
}
