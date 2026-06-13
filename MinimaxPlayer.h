#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "Player.h"

class MinimaxPlayer : public Player
{
public:
    MinimaxPlayer(int depth);

    void play(State& st) override;

private:
    int maxDepth;

    int minimax(State st, int depth);
};

#endif