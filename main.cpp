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
#include <stdio.h>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>

#include "let.hpp"

#include "GameState.hpp"
#include "Video.hpp"
#include "Input.hpp"

using namespace Engine;
using namespace GUI;

using namespace Mammut;

void gameLoop( void );
int gameLoopStep( GameState& state );

int main()
{
    // fully initialize everything we need from SDL2
    SDL_SetMainReady();
    SDL_Init( SDL_INIT_EVERYTHING );
    atexit( SDL_Quit );
    
    IMG_Init( IMG_INIT_PNG | IMG_INIT_JPG );
    atexit( IMG_Quit );
    
    TTF_Init();
    atexit( TTF_Quit );
    
    // initialize GLEW and tell it that we want to use new features
    glewExperimental = GL_TRUE;
    glewInit();
    
    gameLoop();
    
    exit( 0 );
}

void gameLoop()
{
    Window window( SDL_WINDOW_RESIZABLE
                 | SDL_WINDOW_SHOWN
                 );
    
    let* state = new GameState( window.createRenderer() );
    
    while ( gameLoopStep( *state ) );
    
    delete state;
}

// returns 0 to break loop
int gameLoopStep( GameState& state )
{
    SDL_Event ev;
    while ( SDL_PollEvent( &ev ) ) {
        if ( inputProcessor( ev, state ) ) {
            // Okay, do nothing.
        } else {
            // safely quit
            return 0;
        }
    }
    
    if ( state.step() ) {
        // Okay, do nothing.
    } else {
        // safely quit
        return 0;
    }
    
    state.draw();
    
    return 1;
}
