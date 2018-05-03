#include "GameLogic.hpp"

#include <assert.h>

using namespace Mammut;

Player::Player( std::string      aname
              , Engine::Texture* tex
              , const int        index
              )
    : name( aname )
    , index( index )
    , player_tex( tex )
    , has_spear_card( true )
    , has_berry_card( true )
    , is_carrying_point( false )
    , points( 0 )
    , turns_left_to_skip( 0 )
{
    assert( player_tex != nullptr );
}

GameBoard::GameBoard( Engine::Texture* tex )
    : player_positions { CAVE, CAVE, CAVE, CAVE }
    , board_tex( tex )
{
    assert( board_tex != nullptr );
}

void Mammut::executeGameTurn( const int      player_count
                            , int&           current_player
                            , GameBoard&     board
                            , Player* const  players // array of players, length 4
                            , const bool           spear_card_played
                            , const int            spear_card_target_index
                            , const bool           berry_card_played
                            , const int            diceroll_result
                            , const MoveDirection  move_direction
                            )
{
    let current_player_index = current_player > 4 ? 3
                             : current_player < 1 ? 1
                             : current_player - 1;
    let next_player_index = current_player_index > 2 ? 0
                          : current_player_index + 1;
    
    if ( spear_card_played && players[current_player_index].has_spear_card ) {
        players[current_player_index].has_spear_card = false;
        if ( spear_card_target_index > -1 && spear_card_target_index < 4 ) {
            players[spear_card_target_index].turns_left_to_skip++;
        } else {
            players[current_player_index].turns_left_to_skip++;
        }
    }
    
    if ( berry_card_played ) {
        players[current_player_index].has_berry_card = false;
        next_player_index = current_player_index;
    }
    
    switch ( move_direction ) {
        case MoveDirection::Left:
        movedirection_left:
            board.player_positions[current_player_index] -= diceroll_result;
            break;
        case MoveDirection::Right:
        movedirection_right:
            board.player_positions[current_player_index] += diceroll_result;
            break;
        case MoveDirection::Undecided:
            if ( players[current_player_index].is_carrying_point ) {
                goto movedirection_left;
            } else {
                goto movedirection_right;
            }
            break;
    }
    
    // clamp player player position
    if ( board.player_positions[current_player_index] < 0 ) {
        board.player_positions[current_player_index] = 0;
    } else if ( board.player_positions[current_player_index] > 9 ) {
        board.player_positions[current_player_index] = 9;
    }
    
    // general gameplay checks
    // if carrying point and on cave, drop point and increase stored points
    // if on Mammoth, pick up point to carry back to cave
    if (   players[current_player_index].is_carrying_point
        && board.player_positions[current_player_index] == CAVE
       ) {
        players[current_player_index].is_carrying_point = false;
        players[current_player_index].points++;
    } else if ( board.player_positions[current_player_index] == MAMMOTH ) {
        players[current_player_index].is_carrying_point = true;
    }
    
    // if carrying point and on horizontal log, lose point
    if ( players[current_player_index].is_carrying_point
        && board.player_positions[current_player_index] == HORIZONTAL_LOG
       ) {
        players[current_player_index].is_carrying_point = false;
    }
    
    // if on vertical log, skip a turn
    if ( board.player_positions[current_player_index] == VERTICAL_LOG ) {
        players[current_player_index].turns_left_to_skip++;
    }
    
    // see if next player would be targeted by spear card and if yes, skip them
    while ( players[next_player_index].turns_left_to_skip ) {
        players[next_player_index].turns_left_to_skip--;
        next_player_index++;
        if ( next_player_index == player_count ) {
            next_player_index = 0;
        }
    }
    
    current_player = next_player_index + 1;
}
