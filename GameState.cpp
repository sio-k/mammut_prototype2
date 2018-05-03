#include "GameState.hpp"

using namespace Engine;
using namespace Mammut;

GameState::GameState( Renderer& ren
                    , int playercount
                    )
    : renderer( ren )
    , board ( ren.loadTexture( "/home/sioclya/cpp/c-spiel/src/Mammut/prototype_2/images/background.jpg" ) )
    , players { Player( "Player 1"
                      , ren.loadTexture( "/home/sioclya/cpp/c-spiel/src/Mammut/prototype_2/images/player0.png" )
                      , 0
                      )
              , Player( "Player 2"
                      , ren.loadTexture( "/home/sioclya/cpp/c-spiel/src/Mammut/prototype_2/images/player1.png" )
                      , 1
                      )
              , Player( "Player 3"
                      , ren.loadTexture( "/home/sioclya/cpp/c-spiel/src/Mammut/prototype_2/images/player2.png" )
                      , 2
                      )
              , Player( "Player 4"
                      , ren.loadTexture( "/home/sioclya/cpp/c-spiel/src/Mammut/prototype_2/images/player3.png" )
                      , 3
                      )
              }
    , dice()
    , player_count( playercount )
    , current_player(           1 )
    , spear_card_target_index( -1 )
    , spear_card_played(        false )
    , berry_card_played(        false )
    , diceroll_result(          0 )
    , move_direction( MoveDirection::Undecided )
    , quit( false )
    , roll_dice(              false )
    , play_spear_card(        false )
    , play_berry_card(        false )
    , end_turn(               false )
    , change_direction_left(  false )
    , change_direction_right( false )
    , target_player_1(        false )
    , target_player_2(        false )
    , target_player_3(        false )
    , target_player_4(        false )
    , buttons { Button( renderer
                      , "ROLL"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> roll_dice = true;
                                        return;
                                      }
                      , this
                      , 0.3f
                      , 0.05f
                      , 0.2f
                      , 0.1f
                      )
              , Button( renderer
                      , "SPEAR"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> play_spear_card = true;
                                        return;
                                      }
                      , this
                      , 0.75f
                      , 0.1f
                      , 0.2f
                      , 0.1f
                      )
              , Button( renderer
                      , "BERRY"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> play_berry_card = true;
                                        return;
                                      }
                      , this
                      , 0.75f
                      , 0.25f
                      , 0.2f
                      , 0.1f
                      )
              , Button( renderer
                      , "END TURN"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> end_turn = true;
                                        return;
                                      }
                      , this
                      , 0.7f
                      , 0.85f
                      , 0.25f
                      , 0.1f
                      )
              , Button( renderer
                      , ">"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> change_direction_right = true;
                                        return;
                                      }
                      , this
                      , 0.35f
                      , 0.85f
                      , 0.1f
                      , 0.1f
                      )
              , Button( renderer
                      , "<"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> change_direction_left = true;
                                        return;
                                      }
                      , this
                      , 0.2f
                      , 0.85f
                      , 0.1f
                      , 0.1f
                      )
              , Button( renderer
                      , "P1"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> target_player_1 = true;
                                        return;
                                      }
                      , this
                      , 0.75f
                      , 0.45f
                      , 0.1f
                      , 0.1f
                      )
              , Button( renderer
                      , "P2"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> target_player_2 = true;
                                        return;
                                      }
                      , this
                      , 0.85f
                      , 0.45f
                      , 0.1f
                      , 0.1f
                      )
              , Button( renderer
                      , "P3"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> target_player_3 = true;
                                        return;
                                      }
                      , this
                      , 0.75f
                      , 0.55f
                      , 0.1f
                      , 0.1f
                      )
              , Button( renderer
                      , "P4"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> target_player_4 = true;
                                        return;
                                      }
                      , this
                      , 0.85f
                      , 0.55f
                      , 0.1f
                      , 0.1f
                      )
              , Button( renderer
                      , "QUIT"
                      , []( void* o ) { GameState* state = ( GameState* ) o;
                                        state -> quit = true;
                                      }
                      , this
                      , 0.0f
                      , 0.0f
                      , 0.2f
                      , 0.1f
                      )
              }
    , diceroll_result_field( renderer
                           , 0.5f
                           , 0.05f
                           , 0.1f
                           , 0.1f
                           )
    , player_field( renderer
                  , "PLAYER"
                  , 0.3f
                  , 0.15f
                  , 0.2f
                  , 0.1f
                  )
    , player_number_field( renderer
                         , 0.5f
                         , 0.15f
                         , 0.1f
                         , 0.1f
                         )
    , player_score_text_fields { TextField( renderer
                                          , "Player 1 score:"
                                          , 0.05f
                                          , 0.75f
                                          , 0.15f
                                          , 0.05f
                                          )
                               , TextField( renderer
                                          , "Player 2 score:"
                                          , 0.05f
                                          , 0.8f
                                          , 0.15f
                                          , 0.05f
                                          )
                               , TextField( renderer
                                          , "Player 3 score:"
                                          , 0.05f
                                          , 0.85f
                                          , 0.15f
                                          , 0.05f
                                          )
                               , TextField( renderer
                                          , "Player 4 score:"
                                          , 0.05f
                                          , 0.9f
                                          , 0.15f
                                          , 0.05f
                                          )
                               }
    , player_score_number_fields { NumberField( renderer
                                              , 0.2f
                                              , 0.75f
                                              , 0.05f
                                              , 0.05f
                                              )
                                 , NumberField( renderer
                                              , 0.2f
                                              , 0.8f
                                              , 0.05f
                                              , 0.05f
                                              )
                                 , NumberField( renderer
                                              , 0.2f
                                              , 0.85f
                                              , 0.05f
                                              , 0.05f
                                              )
                                 , NumberField( renderer
                                              , 0.2f
                                              , 0.9f
                                              , 0.05f
                                              , 0.05f
                                              )
                                 }
{
    /*
     * GUI element init
     */

    player_number_field.showNumber( current_player );
    
    gui_regenerate_player_scores();
}

GameState::~GameState()
{
}

void GameState::draw()
{
    renderer.clear();
    
    renderer.render( board.board_tex
                   , RenderPosition( renderer
                                   , 0.0f
                                   , 0.0f
                                   , 1.0f
                                   , 1.0f
                                   , 1.0f
                                   )
                   );
    
    for ( Player& p : players ) {
        renderer.render( p.player_tex
                       , RenderPosition( renderer
                                       , ( float ) board.player_positions[p.index] * 0.1f
                                       , 0.2f + ( float ) p.index * 0.2f
                                       , 0.1f
                                       , 0.1f
                                       , 0.5f
                                       )
                       );
    }
    
    for ( Button& b : buttons ) {
        b.draw();
    }
    
    diceroll_result_field.draw();
    player_field.draw();
    player_number_field.draw();
    
    for ( TextField& pstf : player_score_text_fields ) {
        pstf.draw();
    }
    
    for ( NumberField& psnf : player_score_number_fields ) {
        psnf.draw();
    }
    
    renderer.present();
}

void GameState::click( int x, int y )
{
    // convert click coords to normalized (0...1 float) coords
    let normalized_x = ( ( float ) x )
                     / ( ( float ) renderer.width() );
    
    let normalized_y = ( ( float ) y )
                     / ( ( float ) renderer.height() );

    for ( Button& b : buttons ) {
        if ( b.check_hit( normalized_x, normalized_y ) ) {
            b.click();
            break;
        }
    }
}

int GameState::step()
{
    // deal with GUI mutables ( input ) first
    // @{
    if ( quit ) {
        // just quit safely
        return 0;
    }
    
    if ( roll_dice ) {
        if ( diceroll_result < 1 || diceroll_result > 6 ) {
            diceroll_result = ( dice() % 6 ) + 1;
            diceroll_result_field.showNumber( diceroll_result );
        }
    }

    if ( play_spear_card ) {
        spear_card_played = true;
    }
    
    if ( play_berry_card ) {
        berry_card_played = true;
    }
    
    if ( change_direction_left ) {
        move_direction = MoveDirection::Left;
    }
    
    if ( change_direction_right ) {
        move_direction = MoveDirection::Right;
    }
    
    if ( target_player_1 ) {
        spear_card_target_index = 0;
    }
    
    if ( target_player_2 ) {
        spear_card_target_index = 1;
    }
    
    if ( target_player_3 ) {
        if ( player_count > 2 ) {
            spear_card_target_index = 2;
        } else {
            spear_card_target_index = -1;
        }
    }
    
    if ( target_player_4 ) {
        if ( player_count > 3 ) {
            spear_card_target_index = 3;
        } else {
            spear_card_target_index = -1;
        }
    }
    
    if ( end_turn ) {
        if ( diceroll_result < 1 || diceroll_result > 6 ) {
            diceroll_result = ( dice() % 6 ) + 1;
            diceroll_result_field.showNumber( diceroll_result );
        }
        executeGameTurn( player_count
                       , current_player
                       , board
                       , players
                       , spear_card_played
                       , spear_card_target_index
                       , berry_card_played
                       , diceroll_result
                       , move_direction
                       );
        reset_game_logic_mutables_end_of_turn();
        player_number_field.showNumber( current_player );
        gui_regenerate_player_scores();
    }
    // @}
    
    // reset all GUI mutables so they can be set again for the next step
    reset_gui_mutables();
    
    return 1;
}

void GameState::reset_game_logic_mutables()
{
    current_player = 1;
    reset_game_logic_mutables_end_of_turn();
}

void GameState::reset_game_logic_mutables_end_of_turn()
{
    spear_card_target_index = -1;
    spear_card_played = false;
    berry_card_played = false;
    diceroll_result = 0;
    move_direction = MoveDirection::Undecided;
}

void GameState::reset_gui_mutables()
{
    quit = false;
    roll_dice = false;
    play_spear_card = false;
    play_berry_card = false;
    end_turn = false;
    change_direction_left = false;
    change_direction_right = false;
    target_player_1 = false;
    target_player_2 = false;
    target_player_3 = false;
    target_player_4 = false;
}

void GameState::gui_regenerate_player_scores()
{
    for ( int i = 0; i < 4; i++ ) {
        player_score_number_fields[i].showNumber( players[i].points );
    }
}
