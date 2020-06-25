//
// Created by ivan on 24/6/20.
//

#include "ClientProtocol.h"
#include "Socket.h"
#include <vector>
#include <msgpack.hpp>

#include <iostream>

void ClientProtocol::receiveMapInfo() {
    uint32_t msgLength;
    socket.receive((char*)(&msgLength), sizeof(msgLength));
    msgLength = ntohl(msgLength);
    std::vector<char> mapInfo(msgLength);
    socket.receive(mapInfo.data(), mapInfo.size());
    std::string str(mapInfo.begin(), mapInfo.end());
    std::size_t offset = 0;
    msgpack::object_handle oh = msgpack::unpack(str.data(), str.size(), offset);
    msgpack::type::tuple<int32_t, int32_t> mapSize;
    game.setMapSize(std::get<0>(mapSize), std::get<1>(mapSize));
}
