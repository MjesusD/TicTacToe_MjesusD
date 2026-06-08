#include "MinimaxPlayer.h"

#include <limits>
#include <iostream>
#include <algorithm>

using namespace std;

int MinimaxPlayer::minimax(State st)
{
    int winner = st.check_winner();

    // Estados terminales
    if (winner == State::P1)
    {
        return 1; // gana X
    }

    if (winner == State::P2)
    {
        return -1; // gana O
    }

    if (st.full())
    {
        return 0; // empate
    }

    // Turno de X (MAX)
    if (st.get_to_move() == State::P1)
    {
        int best = numeric_limits<int>::min();

        for (auto move : st.legal_moves())
        {
            State child = st;

            child.make_move(move.first, move.second);

            best = max(best, minimax(child));
        }

        return best;
    }

    // Turno de O (MIN)
    int best = numeric_limits<int>::max();

    for (auto move : st.legal_moves())
    {
        State child = st;

        child.make_move(move.first, move.second);

        best = min(best, minimax(child));
    }

    return best;
}

void MinimaxPlayer::play(State& st)
{
    auto moves = st.legal_moves();

    pair<int,int> bestMove = moves[0];

    // Si juega X (MAX)
    if (st.get_to_move() == State::P1)
    {
        int bestScore = numeric_limits<int>::min();

        for (auto move : moves)
        {
            State child = st;

            child.make_move(move.first, move.second);

            int score = minimax(child);

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }
    }
    // Si juega O (MIN)
    else
    {
        int bestScore = numeric_limits<int>::max();

        for (auto move : moves)
        {
            State child = st;

            child.make_move(move.first, move.second);

            int score = minimax(child);

            if (score < bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }
    }

    st.make_move(bestMove.first, bestMove.second);

    cout << "Minimax juega: ("
         << bestMove.first
         << ", "
         << bestMove.second
         << ")" << endl;
         
}