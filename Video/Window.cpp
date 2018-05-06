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

using namespace Engine;

Window::Window( int flags )
    : win( nullptr )
    , ren( nullptr )
{
    win = SDL_CreateWindow( "THIS IS A WINDOW"
                          , SDL_WINDOWPOS_CENTERED
                          , SDL_WINDOWPOS_CENTERED
                          , 640
                          , 480
                          , flags
                          );
    assert( win != nullptr );
}

Window::~Window()
{
    if ( ren ) {
        delete ren;
    }
    SDL_DestroyWindow( win );
}

Renderer& Window::createRenderer()
{
    if ( ren ) {
        return *ren;
    }
    
    // create appropriate renderer; if Window is initialized with SDL_WINDOW_OPENGL,
    // create an OpenGL renderer, otherwise create a standard SDL2 renderer
    let flags = SDL_GetWindowFlags( win );
    if ( flags & SDL_WINDOW_OPENGL ) {
        ren = new GLRenderer( win );
        return *ren;
    } else {
        let* sdlren = SDL_CreateRenderer( win
                                        , -1
                                        ,   SDL_RENDERER_ACCELERATED
                                          | SDL_RENDERER_PRESENTVSYNC
                                        );
        ren = new SDLRenderer( sdlren );
        return *ren;
    }
}
