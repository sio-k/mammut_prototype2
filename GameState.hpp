#pragma once

#include <random>

#include "Video.hpp"

#include "GUI/Button.hpp"
#include "GUI/NumberField.hpp"
#include "GUI/TextField.hpp"

#include "GameLogic.hpp"

namespace Mammut
{

struct GameState
{
    GameState( Engine::Renderer& ren, int playercount = 2 );
    GameState( GameState& ) = delete; // copy constructor currently deleted, would do stupid shit otherwise
    ~GameState();
    
    void draw();
    
    void click( int x, int y );
    
    // returns 0 for some sort of quit event
    int step();
    
    // ostensibly private methods
    void reset_game_logic_mutables();
    void reset_game_logic_mutables_end_of_turn();
    void reset_gui_mutables();
    void gui_regenerate_player_scores();
    // data fields
    Engine::Renderer& renderer;
    
    // game logic elements
    GameBoard board;
    Player    players[4];
    std::default_random_engine dice;
    
    // game logic immutables
    const int player_count = 2;
    
    // game logic mutables (input/output of game logic)
    int current_player = 1; // 1-based!
    int spear_card_target_index = -1; // -1 for random
    bool spear_card_played = false;
    bool berry_card_played = false;
    int diceroll_result = 0;
    MoveDirection move_direction = MoveDirection::Undecided;
    
    // GUI mutables (output of GUI)
    bool quit                   = false;
    bool roll_dice              = false;
    bool play_spear_card        = false;
    bool play_berry_card        = false;
    bool end_turn               = false;
    bool change_direction_left  = false;
    bool change_direction_right = false;
    bool target_player_1        = false;
    bool target_player_2        = false;
    bool target_player_3        = false;
    bool target_player_4        = false;
    
    // GUI elements
    Engine::Button buttons[11];
    
    Engine::NumberField       diceroll_result_field;
    
    const Engine::TextField   player_field;
    Engine::NumberField       player_number_field;
    
    Engine::TextField   player_score_text_fields[4];
    Engine::NumberField player_score_number_fields[4];
};

}
