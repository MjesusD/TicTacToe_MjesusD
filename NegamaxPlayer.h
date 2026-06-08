#ifndef NEGAMAXPLAYER_H
#define NEGAMAXPLAYER_H

#include "Player.h"

class NegamaxPlayer : public Player
{
public:
    void play(State& st) override;

private:
    int negamax(State st);
};

#endif