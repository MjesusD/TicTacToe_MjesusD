#include "NegamaxPlayer.h"

#include <limits>

using namespace std;

int NegamaxPlayer::negamax(State st)
{
    int winner = st.check_winner();

    if (winner != 0)
    {
        return -1;
    }

    if (st.full())
    {
        return 0;
    }

    int best = numeric_limits<int>::min();

    auto moves = st.legal_moves();

    for (auto move : moves)
    {
        State child = st;

        child.make_move(move.first, move.second);

        int score = -negamax(child);

        if (score > best)
        {
            best = score;
        }
    }

    return best;
}

void NegamaxPlayer::play(State& st)
{
    auto moves = st.legal_moves();

    int bestScore = numeric_limits<int>::min();

    int bestX = moves[0].first;
    int bestY = moves[0].second;

    for (auto move : moves)
    {
        State child = st;

        child.make_move(move.first, move.second);

        int score = -negamax(child);

        if (score > bestScore)
        {
            bestScore = score;

            bestX = move.first;
            bestY = move.second;
        }
    }

    st.make_move(bestX, bestY);
    
}