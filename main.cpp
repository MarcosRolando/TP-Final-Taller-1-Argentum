/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include "SDLException.h"
#include <iostream>
#include "Character/Player.h"
#include "Character/NPC.h"
#include "Map/Map.h"
#include <unistd.h>
#include "GameConstants.h"
#include "Timer.h"
//Starts up SDL and creates window
void init();

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
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
		        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
        Timer moveTime;
        TextureRepository repo(*gRenderer);
        SDL_Rect camera = { 0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT };
        PlayerEquipment pEquipment = {MagicHat, ElfHead, BlueTunic, Nothing, LinkedStaff};
        Player player(repo, camera, 40, 30,pEquipment);
        NPC monster(repo, camera, 168, 30, Goblin);
        Map map(repo, camera);
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
                if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP: player.move(UP); break;
                        case SDLK_DOWN: player.move(DOWN); break;
                        case SDLK_LEFT: player.move(LEFT); break;
                        case SDLK_RIGHT: player.move(RIGHT); break;
                        case SDLK_w: monster.move(UP); break;
                        case SDLK_s: monster.move(DOWN); break;
                        case SDLK_a: monster.move(LEFT); break;
                        case SDLK_d: monster.move(RIGHT); break;
                    }
                }
            }

            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            float timeElapsed = 0;
            while (timeElapsed < 16.66) {
                map.render();
                float timeStep = moveTime.getTicks();
                timeElapsed += timeStep; /*milisegundos desde start*/
                timeStep = timeStep / 1000.f;
                player.render(timeStep);
                monster.render(timeStep);
                moveTime.start();

                //Update screen
                SDL_RenderSetLogicalSize(gRenderer, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
                SDL_RenderPresent(gRenderer);
            }
        }
	} catch (SDLException& e) {
	    std::cout << e.what() << std::endl;
	}

	//Free resources and close SDL
	close();

	return 0;
}