#include <SDL.h>
#include <SDL_image.h>
#include "../libs/TPException.h"

//Starts up Graphics and creates window
void init();

//Frees media and shuts down Graphics
void close();

void init()
{
	//Initialize Graphics
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
        throw TPException("Graphics could not initialize! Graphics Error: %s\n", SDL_GetError());
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
            throw TPException("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
        }
	}
}

void close() {
	//Quit Graphics subsystems
	IMG_Quit();
	SDL_Quit();
}

/*
int main(int argc, char* args[]) {
	//Start up Graphics and create window
	try {
        init();
        Window window;
        Timer moveTime;
        TextureRepository repo(window.getRenderer());
        SDL_Rect camera = { 0, 0, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT };
        PlayerEquipment pEquipment = {Hood, HumanHead, PlateArmor, IronShield, GnarledStaff};
        Player player(repo, camera, 11560, 11550,pEquipment);
        NPC monster(repo, camera, 168, 30, Zombie);

        Texture& background = repo.getTexture(Background);

        Spell explosion(repo.getTexture(MagicMissile), camera, TILE_WIDTH*3, TILE_HEIGHT*3);

        Map map(repo, camera);
        Font UIFont("../Graphics/Text/medieval.ttf", 25);
        Font minichatFont("../Graphics/Text/font.ttf", 20);
        PlayerInfoGUI playerInfo(window.getRenderer());
        PlayerInventoryGUI inventoryGui(repo, window.getRenderer());
        //Buscar una buena font para el minichat
        Minichat minichat(window.getRenderer());
        Selector selector;

        Text clickPos(UIFont, window.getRenderer());

        SoundRepository soundRepo;
        SoundPlayer soundPlayer(soundRepo);
        soundPlayer.playMusic();

        //Me pide que le agregue class xq se confunde con el enum de texturas
        class MainMenu mainMenu(repo.getTexture(MainMenu),window, UIFont);

        //Main loop flag
        bool quit = false;

        //Setea un cursor custom
        SDL_Surface *surface = NULL;
        SDL_Cursor *cursor = NULL;
        surface = SDL_LoadBMP("../../clientSide/Images/UI/Cursor.bmp");
        if (!surface) {
            return 0;
        }
        cursor = SDL_CreateColorCursor(surface, 0, 0);
        if (!cursor) {
            return 0;
        }
        SDL_SetCursor(cursor);

        //Menu principal
        //mainMenu.loop(quit);

        //Event handler
        SDL_Event e;

        //While application is running
        while( !quit )
        {
            int xPlayer, yPlayer;
            //Esto capaz lo cambiamos de lugar despues
            xPlayer = player.getXPosition();
            yPlayer = player.getYPosition();
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                selector.handleEvent(e, xPlayer, yPlayer, window);
                minichat.handleEvent(e, window);
                window.handleEvent(e);

                std::string a = " ";//Para probar lo del minichat

                if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                            a = "up";
                            minichat.queueText(a);
                            player.move(UP);
                            break;
                        case SDLK_DOWN:
                            a = "down";
                            minichat.queueText(a);
                            player.move(DOWN);
                            break;
                        case SDLK_LEFT:
                            a = "left";
                            minichat.queueText(a);
                            player.move(LEFT);
                            break;
                        case SDLK_RIGHT:
                            a = "right";
                            minichat.queueText(a);
                            player.move(RIGHT);
                            break;
                        case SDLK_SPACE://Esto es para probar pausar la musica
                            if (!soundPlayer.isMusicPlaying()) {
                                soundPlayer.pauseMusic();
                            } else {
                                soundPlayer.playMusic();
                            }
                            break;
                    }
                }
            }

            if (!window.isMinimized()) {
                float timeElapsed = 0;
                while (timeElapsed < 100) {
                    //Clear screen
                    window.clear();

                    //Screen
                    window.setViewport(ScreenViewport);
                    background.render(0, 0);

                    //Map
                    window.setViewport(MapViewport);
                    map.renderGround();
                    float timeStep = moveTime.getTicks();
                    timeElapsed += timeStep;

                    //Outline del tile seleccionado. Ver si lo ponemos en Map
                    SDL_Rect fillRect = {selector.getSelectedTileXToRender
                                         (xPlayer),
                                         selector.getSelectedTileYToRender(yPlayer),
                                         128, 128};
                    SDL_SetRenderDrawColor(&window.getRenderer(), 0xFF,
                                           0x00, 0x00, 0xFF);
                    SDL_RenderDrawRect( &window.getRenderer(), &fillRect );


                    timeStep = timeStep / 1000.f;
                    player.render(timeStep);
                    monster.render(timeStep);
                    map.renderNPCS(timeStep);
                    explosion.render(timeStep);
                    map.renderStructures();
                    moveTime.start();

                    //Inventory
                    window.setViewport(InventoryViewport);
                    inventoryGui.updateGold(1000);
                    inventoryGui.render(selector.getInventorySlot());

                    clickPos.updateText("ClickX: " + std::to_string(selector.getSelectedTileX()) +
                    "   ClickY: " + std::to_string(selector.getSelectedTileY
                    ()));//Debugging

                    clickPos.render(150,100, {0xFF,0xFF,0xFF});

                    //PlayerInfo
                    window.setViewport(PlayerInfoViewport);

                    //Minichat
                    window.setViewport(MinichatViewport);
                    minichat.render();
                    window.show();
                    soundPlayer.playSounds();
                    //Dejo esto comentado aca xq me sirve para ver los vewports
                    //SDL_Rect fillRect = {0, 0, DEFAULT_MAP_WIDTH, 45};
                    SDL_SetRenderDrawColor(&window.getRenderer(), 0xFF,
                                           0x00, 0x00, 0xFF);
                    SDL_RenderFillRect( &window.getRenderer(), &fillRect);
                }
            }
        }
	} catch (TPException& e) {
	    std::cerr << e.what() << std::endl;
	} catch (...) {
	    std::cerr << "No se que paso pero algo rompio xd" << std::endl;
	}
	//Free resources and close Graphics
	close();

	return 0;
}*/

#include "Client/ArgentumClientSide.h"
int main(int argc, char** argv) {
    return ArgentumClientSide::run(argc, argv);
}
