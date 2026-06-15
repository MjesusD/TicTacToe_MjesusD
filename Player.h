#ifndef PLAYER_H
#define PLAYER_H

#include "State.h"
#include "SearchStats.h"

class Player
{
public:

    virtual void play(State & st) = 0;

    virtual SearchStats getStats() const
    {
        return SearchStats();
    }

    virtual ~Player() {}
};

#endif