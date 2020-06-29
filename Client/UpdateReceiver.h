//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATERECEIVER_H
#define ARGENTUM_UPDATERECEIVER_H

#include "Thread.h"
#include "BlockingQueue.hpp"

class Socket;

class UpdateReceiver : public Thread {
private:
    //BlockingQueue<std::unique_ptr<UpdateEvent>> updates;
    //Socket& socket;

};


#endif //ARGENTUM_UPDATERECEIVER_H
