//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATERECEIVER_H
#define ARGENTUM_UPDATERECEIVER_H

#include "../../libs/Thread.h"
#include "Update.h"
#include "ClientProtocol.h"
#include <msgpack.hpp>

class UpdateEvent;
class Socket;
class UpdateManager;

class UpdateReceiver : public Thread {
private:
    ClientProtocol& protocol;
    UpdateManager& updateManager;
    Update currentUpdate;
    msgpack::object_handle handler;
    std::size_t offset{0};
    Socket& socket;
    std::vector<char> buffer;
    bool& quit;

public:
    UpdateReceiver(ClientProtocol& protocol, UpdateManager& _updateManager,
                Socket& _socket, bool& _quit) : protocol(protocol),
                updateManager(_updateManager), socket(_socket), quit(_quit) {}

    void run() override;

private:
    void _processAttack();
    void _processCreateItem();
    void _processUnequip();
    void _processUpdate(uint32_t msgLength);
    void _processRemoveEntity();
    void _processMoveUpdate();
    void _receivePlayerData();
    void _processCreateEntity();
    void _processEquipped();
    void _processPlayerDeath();
    void _processDestroyItem();
    void _processTeleportEntity();
    void _processPlayerResurrect();
};


#endif //ARGENTUM_UPDATERECEIVER_H
