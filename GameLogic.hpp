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

#include <string>

#include "let.hpp"

#include "Video.hpp"

namespace Mammut
{

enum PlayerPosition { MAMMOTH        = 9
                    , LOG_1          = 8
                    , LOG_2          = 7
                    , HORIZONTAL_LOG = 6
                    , LOG_4          = 5
                    , LOG_5          = 4
                    , LOG_6          = 3
                    , VERTICAL_LOG   = 2
                    , LOG_8          = 1
                    , CAVE           = 0
                    };

enum class MoveDirection { Left // towards cave
                         , Right // towards mammoth
                         , Undecided
                         };

struct Player
{
    Player( std::string      aname
          , Engine::Texture* tex
          , const int        index
          );
    const std::string name;
    const int   index = -1; // 0 - 3
    
    Engine::Texture* player_tex = nullptr;
    
    bool has_spear_card = true;
    bool has_berry_card = true;
    
    bool is_carrying_point = false;
    
    int points = 0;
    
    int turns_left_to_skip = 0; // turns left for this player to skip; incremented by targeting player with the spear card
};

struct GameBoard
{
    GameBoard( Engine::Texture* tex );
    int              player_positions[4] = { CAVE, CAVE, CAVE, CAVE };
    Engine::Texture* board_tex           = nullptr;
};

void executeGameTurn( const int      player_count
                    , int&           current_player
                    , GameBoard&     board
                    , Player* const        players // array of players, length 4
                    , const bool           spear_card_played
                    , const int            spear_card_target_index
                    , const bool           berry_card_played
                    , const int            diceroll_result
                    , const MoveDirection  move_direction
                    );

}
