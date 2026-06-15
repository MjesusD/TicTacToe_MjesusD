#ifndef NEGAMAXPLAYER_H
#define NEGAMAXPLAYER_H

#include "Player.h"
#include "SearchStats.h"

class NegamaxPlayer : public Player
{
public:

    NegamaxPlayer(int depth);

    void play(State& st) override;

    SearchStats getStats() const override
    {
        return totalStats;
    }

private:

    int maxDepth;

    int negamax(State st, int depth);

    SearchStats stats;       // jugada actual

    SearchStats totalStats;  // partida completa
};

#endif