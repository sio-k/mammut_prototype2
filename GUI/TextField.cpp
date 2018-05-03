#include "TextField.hpp"

using namespace Engine;

TextField::TextField( Renderer& renderer
                    , const std::string text
                    , const float position_x
                    , const float position_y
                    , const float size_x
                    , const float size_y
                    , const SDL_Color background_color
                    , const SDL_Color text_color
                    )
    : background( renderer 
                , position_x
                , position_y
                , size_x
                , size_y
                , background_color
                )
    , text( renderer 
          , text
          , position_x
          , position_y
          , size_x
          , size_y
          , text_color
          )
{
}

TextField::~TextField()
{
}

void TextField::draw() const
{
    background.draw();
    text.draw();
}
