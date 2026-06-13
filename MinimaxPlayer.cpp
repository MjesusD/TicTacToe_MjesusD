#include "MinimaxPlayer.h"

#include <limits>
#include <iostream>
#include <algorithm>

using namespace std;

MinimaxPlayer::MinimaxPlayer(int depth)
{
    maxDepth = depth;
}

int MinimaxPlayer::minimax(State st, int depth)
{
    int winner = st.check_winner();

    // Estados terminales
    if (winner == State::P1)
    {
        return 10000;
    }

    if (winner == State::P2)
    {
        return -10000;
    }

    if (st.full())
    {
        return 0;
    }

    // Corte por profundidad
    if (depth >= maxDepth)
    {
        return st.heuristic();
    }

    // MAX = X
    if (st.get_to_move() == State::P1)
    {
        int best = numeric_limits<int>::min();

        for (auto move : st.legal_moves())
        {
            State child = st;

            child.make_move(move.first, move.second);

            best = max(best,
                       minimax(child, depth + 1));
        }

        return best;
    }

    // MIN = O
    int best = numeric_limits<int>::max();

    for (auto move : st.legal_moves())
    {
        State child = st;

        child.make_move(move.first, move.second);

        best = min(best,
                   minimax(child, depth + 1));
    }

    return best;
}

void MinimaxPlayer::play(State& st)
{
    auto moves = st.legal_moves();

    if (moves.empty())
    {
        return;
    }

    pair<int,int> bestMove = moves[0];

    // X maximiza
    if (st.get_to_move() == State::P1)
    {
        int bestScore = numeric_limits<int>::min();

        for (auto move : moves)
        {
            State child = st;

            child.make_move(move.first, move.second);

            int score = minimax(child, 1);

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }
    }
    // O minimiza
    else
    {
        int bestScore = numeric_limits<int>::max();

        for (auto move : moves)
        {
            State child = st;

            child.make_move(move.first, move.second);

            int score = minimax(child, 1);

            if (score < bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }
    }

    st.make_move(bestMove.first,
                 bestMove.second);

    cout << "Minimax juega: ("
         << bestMove.first
         << ", "
         << bestMove.second
         << ")" << endl;
}