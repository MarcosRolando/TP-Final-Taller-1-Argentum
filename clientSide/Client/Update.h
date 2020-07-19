//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATE_H
#define ARGENTUM_UPDATE_H

#include <queue>
#include <memory>
#include "../UpdateEvents/UpdateEvent.h"

class Update {
private:
    std::queue<std::unique_ptr<UpdateEvent>> events;

public:
    Update() = default;
    Update(Update&& other) noexcept;
    void push(std::unique_ptr<UpdateEvent> element);
    std::unique_ptr<UpdateEvent> pop();
    bool empty();
};

#endif //ARGENTUM_UPDATE_H
