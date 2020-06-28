//
// Created by marcos on 6/28/20.
//

#ifndef ARGENTUM_PLAYERLOADER_H
#define ARGENTUM_PLAYERLOADER_H

class Game;
class PlayerProxy;

class PlayerLoader {
private:
    Game& game;

public:
    PlayerLoader(Game& _game) : game(_game) {}
    PlayerProxy getPlayer(/*recibe el nickname, lo busca en el archivo, le pasa los datos a game y game le devuelve la referencia*/);
};


#endif //ARGENTUM_PLAYERLOADER_H
