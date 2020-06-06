/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "SDLException.h"
#include <iostream>
#include "Texture.h"

#define SCALE 3

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
void init();

//Loads media
void loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

void init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
        throw SDLException("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
            throw SDLException("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
                throw SDLException("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
                    throw SDLException("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
				}
			}
		}
	}
}

void loadHeadMedia(Texture& headSpriteSheetTexture) {
	try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        headSpriteSheetTexture.loadFromFile( "../Images/Heads/HumanHead.png", key);
        headSpriteSheetTexture.addSprite(0, 0, 17, 15);
        headSpriteSheetTexture.addSprite(17, 0, 17, 15);
        headSpriteSheetTexture.addSprite(34, 0, 17, 15);
        headSpriteSheetTexture.addSprite(51, 0, 17, 15);
	} catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
	}
}

void loadBodyMedia(Texture& bodySpriteSheetTexture) {
    try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        headSpriteSheetTexture.loadFromFile( "../Images/Heads/HumanHead.png", key);
        headSpriteSheetTexture.addSprite(0, 0, 17, 15);
        headSpriteSheetTexture.addSprite(17, 0, 17, 15);
        headSpriteSheetTexture.addSprite(34, 0, 17, 15);
        headSpriteSheetTexture.addSprite(51, 0, 17, 15);
    } catch (SDLException& e) {
        throw SDLException("Failed to load sprite sheet texture!\n");
    }
}

void close() {
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = nullptr;
	gRenderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {

	//Start up SDL and create window
	try {
        init();
        Texture headSpriteSheetTexture(*gRenderer);
        Texture bodySpriteSheetTexture(*gRenderer);
        loadHeadMedia(headSpriteSheetTexture);
        loadBodyMedia(bodySpriteSheetTexture);
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
            }

            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            //Render top left sprite
            headSpriteSheetTexture.render( 0, 0, 0, SCALE );

            //Render top right sprite
            headSpriteSheetTexture.render( SCREEN_WIDTH -
                                headSpriteSheetTexture.getSpriteDimensions(1).width*SCALE,
                                0, 1, SCALE );

            //Render bottom left sprite
            headSpriteSheetTexture.render( 0, SCREEN_HEIGHT -
                        headSpriteSheetTexture.getSpriteDimensions(2).height*SCALE,
                                                        2, SCALE );

            //Render bottom right sprite
            headSpriteSheetTexture.render( SCREEN_WIDTH -
            headSpriteSheetTexture.getSpriteDimensions(3).width*SCALE,
            SCREEN_HEIGHT - headSpriteSheetTexture.getSpriteDimensions(3).width*SCALE,
            3, SCALE );

            //Update screen
            SDL_RenderPresent( gRenderer );
        }
	} catch (SDLException& e) {
	    std::cout << e.what() << std::endl;
	}

	//Free resources and close SDL
	close();

	return 0;
}