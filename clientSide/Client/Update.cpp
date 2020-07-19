//
// Created by marcos on 19/7/20.
//

#include "Update.h"

void Update::push(std::unique_ptr<UpdateEvent> element) {
    events.push(std::move(element));
}

std::unique_ptr<UpdateEvent> Update::pop() {
    std::unique_ptr<UpdateEvent> element = std::move(events.front());
    events.pop();
    return element;
}

bool Update::empty() {
    return events.empty();
}

Update::Update(Update&& other) noexcept {
    events = std::move(other.events);
}