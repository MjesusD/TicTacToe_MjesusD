#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "Player.h"

class MinimaxPlayer : public Player
{
public:
    void play(State& st) override;

private:
    int minimax(State st);
};

#endif