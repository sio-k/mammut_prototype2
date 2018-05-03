#pragma once

#include <SDL2/SDL_events.h>

#include "GameState.hpp"

namespace Engine
{

// returns 0 for critical failure or having to exit
int inputProcessor( const SDL_Event& ev, Mammut::GameState& state );

}
