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
#include "Input.hpp"

using namespace Engine;

int Engine::inputProcessor( const SDL_Event& ev, Mammut::GameState& state )
{
    switch ( ev.type ) {
        
        /* quit conditions */
        case SDL_QUIT:
            return 0;
            break;
        case SDL_APP_TERMINATING:
            return 0;
            break;
        case SDL_APP_LOWMEMORY:
            return 0;
            break;
        case SDL_RENDER_DEVICE_RESET:
            // renderer textures invalid
            return 0;
            break;
            
        /* non-quit (user input) events that are handled */
        case SDL_KEYDOWN:
            // NOTE: ignored except for ESC, which quits
            if ( ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE ) {
                return 0;
            }
            break;
        case SDL_KEYUP:
            // TODO: switch for temporary controls to allow controlling game 
            //       from keyboard
            break;
        case SDL_MOUSEMOTION:
            // NOTE: not interesting
            break;
        case SDL_MOUSEBUTTONUP:
            // NOTE: ignored
            break;
        case SDL_MOUSEBUTTONDOWN:
            // we'll take any mouse button
            state.click( ev.button.x, ev.button.y );
            break;
        case SDL_MOUSEWHEEL:
            // NOTE: ignored
            break;
    }
    return 1; // success
}
