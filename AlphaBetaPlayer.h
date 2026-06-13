#ifndef ALPHABETAPLAYER_H
#define ALPHABETAPLAYER_H

#include "Player.h"

class AlphaBetaPlayer : public Player
{
public:
    void play(State& st) override;

private:
    int alphabeta(State st, int alpha, int beta);
};

#endif