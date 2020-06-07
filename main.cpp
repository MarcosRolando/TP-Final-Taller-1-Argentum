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
        bodySpriteSheetTexture.loadFromFile( "../Images/Clothing/PlateArmor.png", key);

        /*Front*/
        bodySpriteSheetTexture.addSprite(0, 0, 25, 45);
        bodySpriteSheetTexture.addSprite(25, 0, 25, 45);
        bodySpriteSheetTexture.addSprite(50, 0, 25, 45);
        bodySpriteSheetTexture.addSprite(75, 0, 25, 45);
        bodySpriteSheetTexture.addSprite(100, 0, 25, 45);
        bodySpriteSheetTexture.addSprite(125, 0, 25, 45);

        /*Back*/
        bodySpriteSheetTexture.addSprite(0, 45, 25, 45);
        bodySpriteSheetTexture.addSprite(25, 45, 25, 45);
        bodySpriteSheetTexture.addSprite(50, 45, 25, 45);
        bodySpriteSheetTexture.addSprite(75, 45, 25, 45);
        bodySpriteSheetTexture.addSprite(100, 45, 25, 45);
        bodySpriteSheetTexture.addSprite(125, 45, 25, 45);

        /*Left*/
        bodySpriteSheetTexture.addSprite(0, 90, 25, 45);
        bodySpriteSheetTexture.addSprite(25, 90, 25, 45);
        bodySpriteSheetTexture.addSprite(50, 90, 25, 45);
        bodySpriteSheetTexture.addSprite(75, 90, 25, 45);
        bodySpriteSheetTexture.addSprite(100, 90, 25, 45);
        bodySpriteSheetTexture.addSprite(100, 90, 25, 45); /*lo cargo 2 veces para simplificar la cuenta*/

        /*Rigth*/
        bodySpriteSheetTexture.addSprite(0, 135, 25, 45);
        bodySpriteSheetTexture.addSprite(25, 135, 25, 45);
        bodySpriteSheetTexture.addSprite(50, 135, 25, 45);
        bodySpriteSheetTexture.addSprite(75, 135, 25, 45);
        bodySpriteSheetTexture.addSprite(100, 135, 25, 45);
        bodySpriteSheetTexture.addSprite(100, 135, 25, 45); /*lo cargo 2 veces para simplificar la cuenta*/

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

            //Render front sprite
            headSpriteSheetTexture.render( 12, 9, 0, SCALE);

            bodySpriteSheetTexture.render( 0, 35,i/2000 + 0, SCALE );

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