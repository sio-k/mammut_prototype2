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
#include "../Video.hpp"

#include "../let.hpp"

#include <GL/glew.h>

#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>

#include <assert.h>

using namespace Engine;

GLRenderPos::GLRenderPos( GLfloat x
                        , GLfloat y
                        , GLfloat w
                        , GLfloat h
                        , GLfloat depth
                        )
    : rect { { x    , y    , depth } // counterclockwise
           , { x    , y + h, depth }
           , { x + w, y + h, depth }
           , { x + w, y    , depth }
           }
{
}

GLRenderer::GLRenderer( SDL_Window* win )
    : window( win )
    , context( nullptr )
    , textures()
{
    // get window size
    int w = 0;
    int h = 0;
    SDL_GetWindowSize( window, &w, &h );
    size_x = w;
    size_y = h;
    
    // OpenGL setup
    
    // using GL2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION
                       , 2
                       );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION
                       , 1
                       );
    // enable double buffering
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER
                       , 1
                       );
    
    // setup done, create rendering context
    context = SDL_GL_CreateContext( window );
    assert( context != nullptr );
    
    // enable vertical sync
    SDL_GL_SetSwapInterval( 1 );

    // enable 2d textures
    glEnable( GL_TEXTURE_2D );

    glShadeModel( GL_SMOOTH );
    
    // Initialize Projection Matrix and set coord system to engine's normalized coord system
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(  0.0f // left end
           ,  1.0f // right end
           ,  1.0f // bottom end
           ,  0.0f // top end
           ,  0.0f // near end
           ,  1.0f // far end
           );

    // Initialize Modelview Matrix to Identity Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    // save default modelview matrix to modelview matrix stack
    glPushMatrix();
}

GLRenderer::~GLRenderer()
{
    unloadAllTextures();
    // destroy our GL context
    SDL_GL_DeleteContext( context );
}

void GLRenderer::clear()
{
    // recheck window size and if it has changed, reset matrices
    int w = 0;
    int h = 0;
    SDL_GL_GetDrawableSize( window, &w, &h );
    if ( size_x != w || size_y != h ) {
        // set new width and height
        size_x = w;
        size_y = h;
    
        // set new viewport width and height
        glViewport( 0, 0, size_x, size_y );

        // make sure orthographic projection matrix is still the same
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho(  0.0f // left end
               ,  1.0f // right end
               ,  1.0f  // bottom end
               ,  0.0f  // top end
               ,  1.0f  // near end
               , -1.0f  // far end
               );
    }
    
    // reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    // move to top left nearest point ( 0, 0, 0 )
    glTranslatef( 0.0f, 0.0f, 0.0f );
    
    // set clear color
    glClearColor( 0.1f // R
                , 0.1f // G
                , 0.1f // B
                , 0.1f // A
                );
    // clear colors and depth buffer
    glClear( GL_COLOR_BUFFER_BIT
           | GL_DEPTH_BUFFER_BIT
           );
}

void GLRenderer::render( Texture* torender, RenderPosition target )
{
    GLuint tex = 0;
    // dirty hack
    memcpy( &tex, &torender, sizeof( tex ) );
    
    glBindTexture( GL_TEXTURE_2D, tex );
    
    glBegin( GL_QUADS );
        //glColor3f( 0.5f, 0.5f, 0.5f );
        let* dst = target.gl.rect;
        
        glTexCoord2f( 0.0f, 0.0f );
        glVertex2f( dst[0][0], dst[0][1] );
        
        glTexCoord2f( 0.0f, 1.0f );
        glVertex2f( dst[1][0], dst[1][1] );
        
        glTexCoord2f( 1.0f, 1.0f );
        glVertex2f( dst[2][0], dst[2][1] );
        
        glTexCoord2f( 1.0f, 0.0f );
        glVertex2f( dst[3][0], dst[3][1] );
    glEnd();
    
    glBindTexture( GL_TEXTURE_2D, 0 );
}

void GLRenderer::present()
{
    SDL_GL_SwapWindow( window );
}

Texture* GLRenderer::loadTexture( const char *const path )
{
    assert( path != nullptr );
    
    SDL_Surface* surface = IMG_Load( path );
    assert( surface != nullptr );
    
    Texture* toreturn = getTextureFromSurface( surface );
    SDL_FreeSurface( surface );
    return toreturn;
}

Texture* GLRenderer::getTextureFromSurface( SDL_Surface* old_surface )
{
    assert( old_surface != nullptr );
    
    SDL_Surface* surface = SDL_ConvertSurfaceFormat( old_surface
                                                   , SDL_PIXELFORMAT_RGBA32
                                                   , 0
                                                   );
    assert( surface != nullptr );
    
    GLuint tex_num = 0;
    GLuint width = static_cast< GLuint >( surface -> w );
    GLuint height = static_cast< GLuint >( surface -> h );
    
    // generate a texture id and bind it to be a 2D texture
    glGenTextures( 1, &tex_num );
    glBindTexture( GL_TEXTURE_2D, tex_num );
    
    glTexImage2D( GL_TEXTURE_2D
                , 0
                , GL_RGBA
                , width
                , height
                , 0
                , GL_RGBA
                , GL_UNSIGNED_BYTE
                , surface -> pixels
                );
    
    glTexParameteri( GL_TEXTURE_2D
                   , GL_TEXTURE_MAG_FILTER
                   , GL_LINEAR
                   );
    glTexParameteri( GL_TEXTURE_2D
                   , GL_TEXTURE_MIN_FILTER
                   , GL_LINEAR
                   );
    
    glBindTexture( GL_TEXTURE_2D, 0 );
    
    textures.push_back( tex_num );
    
    GLenum error = glGetError();
    if ( error != GL_NO_ERROR ) {
        perror( "Encountered an error while loading texture" );
    }
    
    SDL_FreeSurface( surface );
    
    // dirty hack
    Texture* tex = nullptr;
    memcpy( &tex, &tex_num, sizeof( GLuint ) );
    return tex;
}

void GLRenderer::unloadAllTextures()
{
    for ( GLuint id : textures ) {
        if ( id != 0 ) {
            glDeleteTextures( 1, &id );
        }
    }
    textures.clear();
}

int GLRenderer::height() const
{
    return size_x;
}

int GLRenderer::width() const
{
    return size_y;
}
