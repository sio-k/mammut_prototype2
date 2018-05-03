#include "NumberField.hpp"

#include <assert.h>

using namespace Engine;
using namespace GUI;

NumberField::NumberField( Renderer& ren
                        , float position_x
                        , float position_y
                        , float size_x
                        , float size_y
                        , SDL_Color background_color
                        , SDL_Color text_color
                        )
    : numbers { TextLayer( ren
                         , "0"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "1"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "2"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "3"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "4"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "5"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "6"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "7"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "8"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              , TextLayer( ren
                         , "9"
                         , position_x
                         , position_y
                         , size_x
                         , size_y
                         , text_color
                         )
              }
    , background( ren
                , position_x
                , position_y
                , size_x
                , size_y
                , background_color
                )
    , current_number( 0 )
{
}

NumberField::~NumberField()
{
}

void NumberField::showNumber( int num )
{
    current_number = num >= 0 && num <= 9 ? num : 0;
}

void NumberField::draw() const
{
    background.draw();
    numbers[current_number].draw();
}
