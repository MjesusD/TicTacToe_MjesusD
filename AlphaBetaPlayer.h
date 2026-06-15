#ifndef ALPHABETAPLAYER_H
#define ALPHABETAPLAYER_H

#include "Player.h"
#include "SearchStats.h"

class AlphaBetaPlayer : public Player
{
public:

    AlphaBetaPlayer(int depth);

    void play(State& st) override;

    SearchStats getStats() const override
    {
        return totalStats;
    }

private:

    int maxDepth;

    int alphabeta(State st, int depth, int alpha, int beta);

    SearchStats stats;       // jugada actual

    SearchStats totalStats;  // partida completa
};

#endif