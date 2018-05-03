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
