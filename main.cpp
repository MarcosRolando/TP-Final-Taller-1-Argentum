//#include "Sounds.h"

/*
int main( int argc, char* args[] )//Para probar la carga y reproduccion de
// sonidos
{
    try {
        Sounds sounds;
        char soundToPlay;
        do {
            std::cout << "Que sonido queres papa" << std::endl;
            std::cin >> soundToPlay;
            switch (soundToPlay) {
                case 'e':
                    sounds.playExplotionSound();
                    break;
                case 'a':
                    sounds.playAttackSound();
                    break;
                case 'm':
                    sounds.playMusic();
                    break;
                case 'p':
                    sounds.pauseMusic();
                    break;
                default:
                    soundToPlay = 'q';
            }
        } while (soundToPlay != 'q');
        sounds.stopMusic();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

	return 0;
}
*/

#include "SDLException.h"
#include "Texture.h"
#include "Font.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

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
            }
        }
    }
}
void close()
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] ){

    try {
        init();//Esto es lo de crear la ventana y el renderer, va a ir a
        // la clase SDL gral
        Texture textTexture(*gRenderer);
        Font textFont("../font.ttf", 32);
        SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
        std::string texto;
        std::cin >> texto;

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
            SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
            SDL_RenderClear( gRenderer );

            textTexture.loadFromRenderedText(texto, textColor,textFont.getFont
            ());

            //Render current frame
            textTexture.render( 0, 0 );

            //Update screen
            SDL_RenderPresent( gRenderer );
        }
    } catch (SDLException& e) {
        std::cout << e.what() << std::endl;
    }

    close();
    return 0;
}

