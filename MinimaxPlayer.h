#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "Player.h"
#include "SearchStats.h"

class MinimaxPlayer : public Player
{
public:
    MinimaxPlayer(int depth);

    void play(State& st) override;

    SearchStats getStats() const override
    {
        return totalStats;
    }

private:
    int maxDepth;

    int minimax(State st, int depth);

    SearchStats stats;       // jugada actual

    SearchStats totalStats;  // partida completa
};

#endif