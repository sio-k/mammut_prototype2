#pragma once
/*
 * Generic Button class. Renders itself to a position on the screen specified by normalized coords (0...1 float).
 */

#include <cstdint>

#include <functional>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include "../Font.hpp"
#include "../Video.hpp"

#include "TextLayer.hpp"
#include "Rectangle.hpp"

namespace Engine
{

struct Button
{
    typedef std::function< void( void* ) > button_function;
    
    Button( Renderer&             renderer
          , const std::string     buttontext = "This is a Button"
          , const button_function onclick    = []( void* ) { return; }
          , void* const           obj        = nullptr 
          , const float           position_x = 0.5f
          , const float           position_y = 0.5f
          , const float           size_x     = 0.1f
          , const float           size_y     = 0.1f
          , const SDL_Color       foreground_color = { 0xFF
                                                     , 0xFF
                                                     , 0xFF
                                                     , 0xFF
                                                     }
          , const SDL_Color       background_color = { 0x13
                                                     , 0x13
                                                     , 0x13
                                                     , 0xFF
                                                     }
          , const SDL_Color       pushed_state_color = { 0x45
                                                       , 0x45
                                                       , 0x45
                                                       , 0xFF
                                                       }
          , const uint32_t        pushed_state_time = 400
          );
    ~Button();
    
    bool check_hit( float x, float y ) const;
    void click();
    void draw() const;

    // data members
    uint32_t timestamp_last_clicked_in_ms = 0; // required to be in "pushed" state for a certain amount of time
    const uint32_t time_in_pushed_state = 400; // ms to remain in pushed state
    
    const float pos_x = 0.0f;
    const float pos_y = 0.0f;
    const float width = 0.0f;
    const float height = 0.0f;
    
    const button_function fn;
    void* const object = nullptr;
    
    const GUI::TextLayer text;
    const GUI::Rectangle background;
    const GUI::Rectangle background_pushed;
};

}
