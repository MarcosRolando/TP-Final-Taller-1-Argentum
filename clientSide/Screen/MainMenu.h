//
// Created by ivan on 23/6/20.
//

#ifndef ARGENTUM_MAINMENU_H
#define ARGENTUM_MAINMENU_H

#include "../Graphics/Text/Text.h"
#include "Window.h"
#include "../../libs/GameEnums.h"

class Socket;
class GameInitializer;

struct GameStartInfo {
    bool createPlayer;
    std::string myNickname;
    GameType::Class myClass;
    GameType::Race myRace;
};

struct Button{
    SDL_Rect buttonEdges;
    SDL_Color color;
    bool available;
};

class MainMenu {
private:
    Window& window;
    Font mainMenuFont;
    Text text;//El texto general. "Exit" "Connect" etc
    Text hostInputText;//Para ver que host pone el usuario
    Text portInputText;//Idem anterior pero con port
    Text nicknameInputText;//idem anterior pero con nickname
    Text errorText;//Para texto de error
    bool hostInput, portInput, nickInput; //Me dicen en donde hice click para ver donde pongo el input
    Texture& mainMenuBackground;
public:
    MainMenu(Texture& texture, Window& window);

    //Toma el host y port e intenta conectarse
    void connectLoop(bool &quit, std::string &_host, std::string &_port, Socket& socket);

    //Deja al player elegir cargar/crear personaje e iniciar la partida
    void playerSelectionLoop(bool& quit, GameInitializer& initializer, Socket& socket);

    ~MainMenu();

private:
    static bool _isInsideRect(int x, int y, SDL_Rect rect);
    void _renderConnectScreen();
    void _attemptToConnect(Socket &socket, bool &finished);
    void _handleTextInput(SDL_Event &e);
    void _handleBackspace();
    void _renderPlayerSelectionScreen();
    void _createPlayer(bool &quit, bool& success, GameInitializer &initializer, Socket &socket);
    void _loadPlayer(bool &quit, bool& success, GameInitializer &initializer, Socket &socket);
    void playerSelection(bool &quit, bool& createPlayer, bool& loadPlayer);

    void
    _connectPlayer(GameInitializer &initializer, Socket &socket, bool &success);

    void _renderLoadPlayerScreen();
};


#endif //ARGENTUM_MAINMENU_H
