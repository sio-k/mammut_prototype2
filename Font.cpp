#include "Font.hpp"

#include "let.hpp"

static TTF_Font* thefont;

void freeFont() {
    TTF_CloseFont( thefont );
}

TTF_Font* Engine::getFont() {
    if ( thefont ) {
        return thefont;
    } else {
        thefont = TTF_OpenFont( FONT_PATH, FONT_SIZE );
        
        atexit( freeFont );
        
        return thefont;
    }
}
