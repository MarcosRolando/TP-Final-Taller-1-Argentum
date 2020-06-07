/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "SDLException.h"
#include <iostream>
#include "PlayerTexture.h"

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
        PlayerTexture player (*gRenderer);
        player.setHeadImage("../Images/Heads/ElfHead.png");
        player.setBodyImage("../Images/Clothing/CommonClothing.png");
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        int i = 0;

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

            player.renderLeft(10, 30, i/2000);
            ++i;
            if (i / 2000 >= 6) i = 0;
/*
            //Render front sprite
            headSpriteSheetTexture.render( 12, 9, 0, SCALE);

            bodySpriteSheetTexture.render( 0, 35, i/2000 + 0, SCALE );

            //Render rigth sprite
            headSpriteSheetTexture.render( SCREEN_WIDTH - 65, 9, 1, SCALE );

            bodySpriteSheetTexture.render( SCREEN_WIDTH - 78, 34, i/2000 + 18, SCALE );

            //Render left sprite
            headSpriteSheetTexture.render( 12, SCREEN_HEIGHT - 160, 2, SCALE);

            bodySpriteSheetTexture.render( 4, SCREEN_HEIGHT - 160 + 26, i/2000 + 12, SCALE );

            //Render back sprite
            headSpriteSheetTexture.render( SCREEN_WIDTH - 65,
            SCREEN_HEIGHT - 160,
            3, SCALE );

            bodySpriteSheetTexture.render( SCREEN_WIDTH - 65 - 12, SCREEN_HEIGHT - 160 + 26, i/2000 + 6, SCALE );

            ++i;

            if (i/2000 >= 6) i = 0;
*/
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