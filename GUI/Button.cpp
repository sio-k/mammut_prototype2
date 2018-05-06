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
#include "Button.hpp"

#include <assert.h>

using namespace Engine;

Button::Button( Renderer&             renderer
              , const std::string     buttontext
              , const button_function onclick
              , void* const           obj
              , const float           position_x
              , const float           position_y
              , const float           size_x
              , const float           size_y
              , const SDL_Color       foreground_color
              , const SDL_Color       background_color
              , const SDL_Color       pushed_state_color
              , const uint32_t        pushed_state_time
              )
    : timestamp_last_clicked_in_ms( 0 )
    , time_in_pushed_state( pushed_state_time )
    , pos_x(  position_x )
    , pos_y(  position_y )
    , width(  size_x     )
    , height( size_y     )
    , fn(     onclick    )
    , object( obj        )
    , text( renderer
          , buttontext
          , position_x
          , position_y
          , size_x
          , size_y
          , foreground_color
          )
    , background( renderer
                , position_x
                , position_y
                , size_x
                , size_y
                , background_color
                )
    , background_pushed( renderer
                       , position_x
                       , position_y
                       , size_x
                       , size_y
                       , pushed_state_color
                       )
{
}

Button::~Button()
{
}

bool Button::check_hit( float x, float y ) const
{
    return x >= pos_x
        && y >= pos_y
        && x <= pos_x + width
        && y <= pos_y + height;
}

void Button::click()
{
    uint32_t current_time = SDL_GetTicks();
    
    // don't do anything if the button is still in clicked state
    if ( timestamp_last_clicked_in_ms + time_in_pushed_state > current_time ) {
        return;
    }
    
    timestamp_last_clicked_in_ms = current_time;
    
    fn( object );
}

void Button::draw() const
{
    if ( SDL_GetTicks() < timestamp_last_clicked_in_ms + time_in_pushed_state ) {
        // button in pushed state
        background_pushed.draw();
    } else {
        background.draw();
    }
    text.draw();
}
