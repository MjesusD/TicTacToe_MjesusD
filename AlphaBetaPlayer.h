#ifndef ALPHABETAPLAYER_H
#define ALPHABETAPLAYER_H

#include "Player.h"

class AlphaBetaPlayer : public Player
{
public:

    AlphaBetaPlayer(int depth);

    void play(State& st) override;

private:

    int maxDepth;

    int alphabeta(State st, int depth, int alpha, int beta);
};

#endif