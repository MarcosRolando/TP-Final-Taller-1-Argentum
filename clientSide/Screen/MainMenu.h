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
    GameType::Class myClass;
    GameType::Race myRace;
};

class MainMenu {
private:
    Window& window;
    Font mainMenuFont;
    Text text;//El texto general. "Exit" "Connect" etc
    Text hostInputText;
    Text portInputText;
    Text nicknameInputText;
    Text errorText;
    Text strength;
    Text constitution;
    Text intelligence;
    Text agility;
    Texture& mainMenuBackground;
    GameStartInfo info;
    bool hostInput, portInput, nicknameInput;

public:
    MainMenu(Texture& texture, Window& window);

    /* Menu Principal antes de iniciar el juego */
    void menuScreen(bool& quit, GameInitializer& initializer, Socket& socket);


    ~MainMenu();

private:
    void _playerSelectionScreen(bool &quit, bool& createPlayer, bool& loadPlayer);
    void _connectScreen(bool &quit, bool& goBack, Socket& socket);
    void _playerCreationScreen(bool &quit, bool& goBack);
    void _playerLoadScreen(bool &quit, bool& goBack);

    void _attemptToConnect(Socket &socket, bool &finished);
    void _connectLoadedPlayer(GameInitializer &initializer, Socket &socket, bool &success);
    void _connectCreatedPlayer(GameInitializer& initializer, Socket& socket, bool& success);

    void _renderPlayerSelectionScreen();
    void _renderConnectScreen();
    void _renderCreatePlayerScreen();
    void _renderLoadPlayerScreen();

    void _renderRace();
    void _renderClass();

    void _updateWarriorSkills();
    void _updatePaladinSkills();
    void _updateClericSkills();
    void _updateWizardSkills();
    void _updateGnomeSkills();
    void _updateDwarfSkills();
    void _updateHumanSkills();
    void _updateElfSkills();

    void _handleTextInput(SDL_Event &e);
    void _handleBackspace();
    void _verifyClassSelection(int x, int y);
    void _verifyRaceSelection(int x, int y);
    static bool _isInsideRect(int x, int y, SDL_Rect rect);
};


#endif //ARGENTUM_MAINMENU_H
