#ifndef PLAYER_H
#define PLAYER_H

#include "State.h"

class Player
{
public:

    virtual void play(State & st) = 0;

    virtual ~Player() {}
};

#endif