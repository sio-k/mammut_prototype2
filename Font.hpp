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
