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
