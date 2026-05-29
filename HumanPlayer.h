#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{
public:

    void play(State & st) override;
};

#endif