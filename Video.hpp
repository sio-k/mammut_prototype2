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
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>

#include <vector>
#include <memory>
#include <unordered_map>

namespace Engine
{

struct Texture; // never defined. This is intentional; You will never have to dereference a reference to this type of texture.

struct Renderer;

struct GLRenderPos
{
    GLRenderPos( GLfloat x
               , GLfloat y
               , GLfloat w
               , GLfloat h
               , GLfloat depth
               );
    
    GLfloat rect[4][3];
};

struct RenderPosition
{
    RenderPosition( Renderer& renderer
                  , float normalized_x
                  , float normalized_y
                  , float normalized_w
                  , float normalized_h
                  , float depth        = -0.5f
                  );
    SDL_Rect    sdl;
    GLRenderPos gl;
};

struct Renderer
{
    virtual ~Renderer() {}
    
    virtual void clear() = 0;
    virtual void render( Texture* torender, RenderPosition target ) = 0;
    virtual void present() = 0;
    
    virtual Texture* loadTexture( const char* const path ) = 0;
    virtual Texture* getTextureFromSurface( SDL_Surface* surface ) = 0;
    virtual void unloadAllTextures() = 0;
    
    virtual int width() const = 0;
    virtual int height() const = 0;
};

struct SDLRenderer
    : Renderer
{
    SDLRenderer( SDL_Renderer* r );
    virtual ~SDLRenderer();
    
    virtual void clear() override; // also gets current renderer size
    virtual void render( /* SDL_Texture */ Texture* torender, RenderPosition target ) override;
    virtual void present() override;
    
    // return SDL_Texture*s
    virtual Texture* loadTexture( const char* const path ) override;
    virtual Texture* getTextureFromSurface( SDL_Surface* surface ) override;
    virtual void unloadAllTextures() override;
    
    virtual int width() const override;
    virtual int height() const override;
    
    // data members
    
    SDL_Renderer* ren = nullptr;
    std::vector< SDL_Texture* > loaded_textures;
    
    int size_x;
    int size_y;
};

struct GLTexture
{
    GLuint tex_num;
    GLuint width;
    GLuint height;
};

struct GLRenderer
    : Renderer
{
    GLRenderer( SDL_Window* win );
    virtual ~GLRenderer();
    
    virtual void clear() override;
    virtual void render( Texture* torender, RenderPosition target ) override;
    virtual void present() override;
    
    virtual Texture* loadTexture( const char* const path ) override;
    virtual Texture* getTextureFromSurface( SDL_Surface* surface ) override;
    virtual void unloadAllTextures() override;
    
    virtual int width() const override;
    virtual int height() const override;
    
    // data members
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;
    
    int size_x = -1;
    int size_y = -1;
    
    std::vector< GLuint > textures;
};

struct Window
{
    Window( int flags = ( SDL_WINDOW_SHOWN
                        | SDL_WINDOW_RESIZABLE
                        | SDL_WINDOW_INPUT_FOCUS
                        )
          );
    ~Window();
    
    Renderer& createRenderer();
    
    SDL_Window* win = nullptr; // automatically created during construction
    Renderer* ren = nullptr;
};

}
