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
