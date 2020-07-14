//
// Created by marcos on 13/7/20.
//

#ifndef ARGENTUM_UPDATEMANAGER_H
#define ARGENTUM_UPDATEMANAGER_H

#include "UpdateQueue.hpp"
#include "../UpdateEvents/UpdateEvent.h"
#include <mutex>
#include <memory>

class UpdateManager {
private:
    std::mutex m;
    std::queue<UpdateQueue<std::unique_ptr<UpdateEvent>>> updates;

public:
    void push(UpdateQueue<std::unique_ptr<UpdateEvent>>& update);
    UpdateQueue<std::unique_ptr<UpdateEvent>> pop();
    int updatesAvailable();
};


#endif //ARGENTUM_UPDATEMANAGER_H
