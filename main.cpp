/*#include <iostream>
#include "SDL/Text.h"
#include "Screen/Window.h"

//Starts up SDL and creates window
void init();

//Frees media and shuts down SDL
void close();

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
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "MipmapLinearNearest" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            throw SDLException("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
        }
    }
}

void close() {
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main() {
    init();
    Window window;
    Font font("../SDL/font.ttf", 100);
    Text health(font, window.getRenderer());
    SDL_Event e;
    bool quit = false;
    //While application is running
    while( !quit ) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            window.handleEvent(e);
        }
        health.updateText("2000");
        health.render(100,100);
        window.show();
    }


    return 0;
}*/
/////////////////////////////////////////////////////////// main de Marcos
// ////////////////////////////////////////////////////////////////////////

/*This source code copyrighted by Lazy Foo' Productions(2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings

#include <SDL.h>
#include <SDL_image.h>
#include "SDL/SDLException.h"
#include <iostream>
#include "Character/Player.h"
#include "Character/NPC.h"
#include "Map/Map.h"
#include "GameConstants.h"
#include "Timer.h"
#include "Screen/Window.h"
#include "SDL/Text.h"

//Starts up SDL and creates window
void init();

//Frees media and shuts down SDL
void close();

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
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "MipmapLinearNearest" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            throw SDLException("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
        }
	}
}

void close() {
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {
	//Start up SDL and create window
	try {
        init();
        //Level camera
        Window window;
        Timer moveTime;
        TextureRepository repo(window.getRenderer());
        SDL_Rect camera = { 0, 0, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT };
        PlayerEquipment pEquipment = {MagicHat, ElfHead, BlueTunic, IronShield, LinkedStaff};
        Player player(repo, camera, 40, 30,pEquipment);
        NPC monster(repo, camera, 168, 30, Guard);
        Map map(repo, camera);
        Font font("../SDL/font.ttf", 25);
        Text health(font, window.getRenderer());

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
                window.handleEvent(e);
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

            float timeElapsed = 0;
            if (!window.isMinimized()) {
                while (timeElapsed < 50) {
                    //Clear screen
                    window.clear();
                    window.setViewport(MapViewport);
                    map.renderGround();
                    float timeStep = moveTime.getTicks();
                    timeElapsed += timeStep;

                    timeStep = timeStep / 1000.f;
                    player.render(timeStep);
                    monster.render(timeStep);
                    map.renderStructures();
                    moveTime.start();

                    //Stats
                    window.setViewport(InventoryViewport);
                    int currHealth = 2000;
                    int totalHealth = 5000;
                    health.updateText("HEALTH: " + std::to_string(currHealth)
                    + "/" + std::to_string(totalHealth));
                    float healthBar = 225 * ((float)currHealth/
                            (float)totalHealth);
                    //Barra de vida
                    SDL_Rect fillRect = {25, 0, (int)healthBar,35 };
                    SDL_SetRenderDrawColor(&window.getRenderer(), 0xFF,
                            0x00, 0x00, 0xFF );
                    SDL_RenderFillRect( &window.getRenderer(), &fillRect );

                    //outline de l abarra de vida
                    SDL_Rect outlineRect = { 25, 0,
                                             225, 35 };
                    SDL_SetRenderDrawColor( &window.getRenderer(), 0x00, 0x00,
                            0x00, 0xFF );
                    SDL_RenderDrawRect( &window.getRenderer(), &outlineRect );
                    health.render(25,0);
                    window.show();
                }
            }

        }
	} catch (SDLException& e) {
	    std::cout << e.what() << std::endl;
	}

	//Free resources and close SDL
	close();

	return 0;
}

