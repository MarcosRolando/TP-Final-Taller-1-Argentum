/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "SDLException.h"
#include <iostream>
#include "Player.h"
#include "Map.h"

#define SCALE 3

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

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
        //Level camera
        SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        EquipmentImages pEquipment = {"", "../Images/Heads/ElfHead.png",
                "../Images/Clothing/CommonClothing.png", ""};
        Player player(*gRenderer, 30, 30,pEquipment);
        Map map(*gRenderer, camera);
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //int i = 0;

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
                player.handleEvent(e);
            }

            player.move();

            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            map.render();
            player.render();
            /*
            player.renderFront(10, 30, i/2000);
            ++i;
            if (i / 2000 >= 6) i = 0;
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