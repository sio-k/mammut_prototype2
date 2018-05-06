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

#include "../let.hpp"

#include <assert.h>
#include <cstdio>

using namespace Engine;

SDLRenderer::SDLRenderer( SDL_Renderer* r )
    : ren( r )
    , loaded_textures()
    , size_x( -1 )
    , size_y( -1 )
{
    assert( ren != nullptr );
}

SDLRenderer::~SDLRenderer()
{
    unloadAllTextures();
    SDL_DestroyRenderer( ren );
}

void SDLRenderer::clear()
{
    SDL_RenderClear( ren );
    
    // get current renderer size
    // TODO: check if this is a fast or slow operation, may be very slow and prove a problem
    SDL_GetRendererOutputSize( ren, &size_x, &size_y );
}

void SDLRenderer::render( Texture* torender, RenderPosition target )
{
    SDL_RenderCopy( ren, ( SDL_Texture*) torender, nullptr, &target.sdl );
}

void SDLRenderer::present()
{
    SDL_RenderPresent( ren );
}

Texture* SDLRenderer::loadTexture( const char* path )
{
    let* temp = IMG_Load( path );
    if ( temp ) {
        let* toreturn = SDL_CreateTextureFromSurface( ren, temp );
        SDL_FreeSurface( temp );
        loaded_textures.push_back( toreturn );
        return ( Texture* ) toreturn;
    } else {
        printf( "%s\n", SDL_GetError() );
        return nullptr;
    }
}

Texture* SDLRenderer::getTextureFromSurface( SDL_Surface* surface )
{
    return ( Texture* ) SDL_CreateTextureFromSurface( ren, surface );
}

void SDLRenderer::unloadAllTextures()
{
    for ( let* tex : loaded_textures ) {
        SDL_DestroyTexture( tex );
    }
    loaded_textures.clear();
}

int SDLRenderer::width() const
{
    return size_x;
}

int SDLRenderer::height() const
{
    return size_y;
}
