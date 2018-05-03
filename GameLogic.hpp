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
