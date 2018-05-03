#pragma once
/*
 * Basic settings and shit for the font we use.
 */

#include <SDL2/SDL_ttf.h>

#define FONT_PATH "./bitstream_vera_1.10/Vera.ttf"
#define FONT_SIZE 32

namespace Engine
{

// NOT THREAD SAFE AT FONT LOAD TIME
TTF_Font* getFont();

}
