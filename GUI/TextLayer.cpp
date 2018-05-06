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
#include "TextLayer.hpp"

#include "../let.hpp"

#include <assert.h>

using namespace Engine;
using namespace GUI;

TextLayer::TextLayer( Renderer& ren
                    , const std::string text
                    , const float position_x
                    , const float position_y
                    , const float size_x
                    , const float size_y
                    , const SDL_Color text_color
                    )
    : renderer( ren )
    , pos_x( position_x )
    , pos_y( position_y )
    , width( size_x )
    , height( size_y )
    , tex( nullptr )
{
    let* surface = TTF_RenderUTF8_Solid( getFont(), text.c_str(), text_color );
    assert( surface != nullptr );
    
    tex = ren.getTextureFromSurface( surface );
    assert( tex != nullptr );
    
    if ( surface != nullptr ) {
        SDL_FreeSurface( surface );
        surface = nullptr;
    }
}

TextLayer::~TextLayer()
{
    // we let the texture get freed by the renderer
}

void TextLayer::draw() const
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
