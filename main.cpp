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
#include "SDL/PlayerInfoGUI.h"
#include "SDL/PlayerInventoryGUI.h"
#include "Spells/Spell.h"

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
        PlayerEquipment pEquipment = {Hood, HumanHead, PlateArmor, IronShield, AshRod};
        Player player(repo, camera, 40, 30,pEquipment);
        NPC monster(repo, camera, 168, 30, Zombie);

        Spell explosion(repo.getTexture(MagicMissil), camera, TILE_WIDTH*3, TILE_HEIGHT*3);

        Map map(repo, camera);
        Font font("../SDL/font.ttf", 25);
        PlayerInfoGUI playerInfo(font, window.getRenderer());
        PlayerInventoryGUI inventoryGui(repo, window.getRenderer());

        //Main loop flag
        bool quit = false;

        int currHealth = 1500;
        int totalHealth = 5000;
        int currXP = 9800;
        int totalXP = 10000;
        int currMana = 980;
        int totalMana = 2000;

        //Event handler
        SDL_Event e;

        //Prueba de llenado de inventario
        inventoryGui.addInventoryItem(CommonClothingDrop);
        inventoryGui.addInventoryItem(MagicHatDrop);
        inventoryGui.addInventoryItem(BlueTunicDrop);
        inventoryGui.addInventoryItem(HealthPotion);
        inventoryGui.addInventoryItem(LinkedStaffDrop);
        inventoryGui.addInventoryItem(LongSwordDrop);
        inventoryGui.addInventoryItem(ManaPotion);


        //LLeno los items equipables
       // inventoryGui.addEquipableItem(BlueTunicDrop, Helmet);
        inventoryGui.addEquipableItem(SimpleBowDrop, Armor);
        inventoryGui.addEquipableItem(WarHammerDrop, Weapon);
       // inventoryGui.addEquipableItem(BlueTunicDrop, Shield);

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
            
            if (!window.isMinimized()) {
                float timeElapsed = 0;
                while (timeElapsed < 100) {
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
                    explosion.render(timeStep);
                    moveTime.start();

                    //Stats
                    window.setViewport(InventoryViewport);
                    inventoryGui.render();
                    playerInfo.updateHealth(currHealth, totalHealth);
                    playerInfo.updateMana(currMana, totalMana);
                    playerInfo.updateXP(currXP, totalXP);
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
