//
// Created by agustin on 23/6/20.
//

#include "List.h"
#include "../../Entities/Player.h"

List::List(Player &_player, Coordinate _npcPosition) : player(_player) {
    npcPosition = _npcPosition;
}

void List::operator()(ServerProtocol& protocol) {
    std::stringstream data;
    player.listFrom(npcPosition, data);

    //HAY QUE AGREGARLO AL MINICHAT DEL PLAYER

}