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

//Scene sprites
SDL_Rect gSpriteClips[ 4 ];

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

void loadMedia(Texture& gSpriteSheetTexture) {
	try {
        //Load sprite sheet texture
        ColorKey_t key = {0, 0, 0};
        gSpriteSheetTexture.loadFromFile( "../Images/Heads/HumanHead.png", key);

        //Set top left sprite
        gSpriteClips[ 0 ].x = 0;
        gSpriteClips[ 0 ].y = 0;
        gSpriteClips[ 0 ].w = 17;
        gSpriteClips[ 0 ].h = 15;

        //Set top right sprite
        gSpriteClips[ 1 ].x = 17;
        gSpriteClips[ 1 ].y = 0;
        gSpriteClips[ 1 ].w = 17;
        gSpriteClips[ 1 ].h = 15;

        //Set bottom left sprite
        gSpriteClips[ 2 ].x = 34;
        gSpriteClips[ 2 ].y = 0;
        gSpriteClips[ 2 ].w = 17;
        gSpriteClips[ 2 ].h = 15;

        //Set bottom right sprite
        gSpriteClips[ 3 ].x = 51;
        gSpriteClips[ 3 ].y = 0;
        gSpriteClips[ 3 ].w = 17;
        gSpriteClips[ 3 ].h = 15;
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
        Texture gSpriteSheetTexture(*gRenderer);
        loadMedia(gSpriteSheetTexture);
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
            gSpriteSheetTexture.render( 0, 0, &gSpriteClips[ 0 ], SCALE );

            //Render top right sprite
            gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 1 ].w*SCALE, 0, &gSpriteClips[ 1 ], SCALE );

            //Render bottom left sprite
            gSpriteSheetTexture.render( 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h*SCALE, &gSpriteClips[ 2 ], SCALE );

            //Render bottom right sprite
            gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 3 ].w*SCALE, SCREEN_HEIGHT - gSpriteClips[ 3 ].h*SCALE, &gSpriteClips[ 3 ], SCALE );

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