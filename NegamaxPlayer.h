#ifndef NEGAMAXPLAYER_H
#define NEGAMAXPLAYER_H

#include "Player.h"

class NegamaxPlayer : public Player
{
public:

    NegamaxPlayer(int depth);

    void play(State& st) override;

private:

    int maxDepth;

    int negamax(State st, int depth);
};

#endif