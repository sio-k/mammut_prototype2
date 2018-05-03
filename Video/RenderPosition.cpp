#include "../Video.hpp"

using namespace Engine;

RenderPosition::RenderPosition( Renderer& renderer
                              , float normalized_x
                              , float normalized_y
                              , float normalized_w
                              , float normalized_h
                              , float depth
                              )
    : sdl { ( int ) ( ( float ) renderer.width()  * normalized_x )
          , ( int ) ( ( float ) renderer.height() * normalized_y )
          , ( int ) ( ( float ) renderer.width()  * normalized_w )
          , ( int ) ( ( float ) renderer.height() * normalized_h )
          }
    , gl( ( GLfloat ) normalized_x
        , ( GLfloat ) normalized_y
        , ( GLfloat ) normalized_w
        , ( GLfloat ) normalized_h
        , ( GLfloat ) depth
        )
{
}
