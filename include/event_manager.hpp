#pragma once

#include <vector>

#include "piece.hpp"

enum class EventType {
    MOVE
};

struct Event {
    EventType type;

    Event(){}
    ~Event(){}

    union {
        struct {
            Position oldPosition;
            Position newPosition;
        } move;
    };

    static Event createMoveEvent(const Position& oldPos, const Position& newPos) {
        Event event;
        event.type = EventType::MOVE;
        event.move.oldPosition = oldPos;
        event.move.newPosition = newPos;
        return event;
    }
};

class Event_Manager {
public:
    void addListener(Piece* listener);
    void removeListener(Piece* listener);
    void dispatchEvent(const Event& event);
private:
    std::vector<Piece*> listeners;
};
