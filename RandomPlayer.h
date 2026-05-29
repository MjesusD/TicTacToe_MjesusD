#ifndef RANDOM_PLAYER_H
#define RANDOM_PLAYER_H

#include "Player.h"

class RandomPlayer : public Player
{
public:

    void play(State & st) override;
};

#endif