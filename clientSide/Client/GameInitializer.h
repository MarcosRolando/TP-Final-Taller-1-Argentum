//
// Created by marcos on 7/1/20.
//

#ifndef ARGENTUM_GAMEINITIALIZER_H
#define ARGENTUM_GAMEINITIALIZER_H

#include <vector>
#include <string>
#include "../../libs/GameEnums.h"

class GameGUI;
class Socket;
class ClientProtocol;

class GameInitializer {
private:
    GameGUI& game;
    Socket& socket;
    ClientProtocol& protocol;

public:
    GameInitializer(GameGUI& _game, Socket& _socket, ClientProtocol& _protocol) :
                    game(_game), socket(_socket), protocol(_protocol) {}

    /* Manda al servidor la informacion para crear un nuevo jugador */
    void createPlayer(const std::string &nickname, GameType::Race race,
                      GameType::Class _class);

    /* Manda al servidor la informacion para cargar un jugador */
    void loadPlayer(const std::string &nickname);

    /* Recibe el estado inicial del juego */
    void initializeGame();

private:
    void _receiveMapInfo();
    void _receiveCurrentGameState();
    void _loadMap(std::vector<char>& buffer);
    void _processAddEntity(std::vector<char>& buffer, std::size_t& offset);
    void _receivePlayerData();
};


#endif //ARGENTUM_GAMEINITIALIZER_H
