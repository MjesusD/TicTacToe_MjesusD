#include "NegamaxPlayer.h"

#include <limits>
#include <iostream>

using namespace std;

NegamaxPlayer::NegamaxPlayer(int depth)
{
    maxDepth = depth;
}

int NegamaxPlayer::negamax(State st, int depth)
{
    int winner = st.check_winner();

    // Nodo terminal
    if (winner != 0)
    {
        if (winner == st.get_to_move())
        {
            return 10000;
        }

        return -10000;
    }

    if (st.full())
    {
        return 0;
    }

    // Corte por profundidad
    if (depth >= maxDepth)
    {
        int h = st.heuristic();

        // evalúa desde el jugador actual
        if (st.get_to_move() == State::P1)
        {
            return h;
        }

        return -h;
    }

    int best = numeric_limits<int>::min();

    for (auto move : st.legal_moves())
    {
        State child = st;

        child.make_move(move.first, move.second);

        int score = -negamax(child, depth + 1);

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

    if (moves.empty())
    {
        return;
    }

    int bestScore = numeric_limits<int>::min();

    int bestX = moves[0].first;
    int bestY = moves[0].second;

    for (auto move : moves)
    {
        State child = st;

        child.make_move(move.first, move.second);

        int score = -negamax(child, 1);

        if (score > bestScore)
        {
            bestScore = score;

            bestX = move.first;
            bestY = move.second;
        }
    }

    st.make_move(bestX, bestY);

    cout << "Negamax juega: ("
         << bestX
         << ", "
         << bestY
         << ")" << endl;
}