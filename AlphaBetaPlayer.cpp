#include "AlphaBetaPlayer.h"

#include <limits>

using namespace std;

int AlphaBetaPlayer::alphabeta(State st, int alpha, int beta)
{
    int winner = st.check_winner();

    if (winner == State::P1)
        return 1;

    if (winner == State::P2)
        return -1;

    if (st.full())
        return 0;

    auto moves = st.legal_moves();

    // MAX (X)
    if (st.get_to_move() == State::P1)
    {
        int value = numeric_limits<int>::min();

        for (auto move : moves)
        {
            State child = st;

            child.make_move(move.first, move.second);

            value = max(value,
                        alphabeta(child, alpha, beta));

            alpha = max(alpha, value);

            // poda
            if (alpha >= beta)
                break;
        }

        return value;
    }

    // MIN (O)
    else
    {
        int value = numeric_limits<int>::max();

        for (auto move : moves)
        {
            State child = st;

            child.make_move(move.first, move.second);

            value = min(value,
                        alphabeta(child, alpha, beta));

            beta = min(beta, value);

            // poda
            if (alpha >= beta)
                break;
        }

        return value;
    }
}

void AlphaBetaPlayer::play(State& st)
{
    auto moves = st.legal_moves();

    int bestX = moves[0].first;
    int bestY = moves[0].second;

    if (st.get_to_move() == State::P1)
    {
        int bestScore = numeric_limits<int>::min();

        for (auto move : moves)
        {
            State child = st;

            child.make_move(move.first, move.second);

            int score =
                alphabeta(child,
                          numeric_limits<int>::min(),
                          numeric_limits<int>::max());

            if (score > bestScore)
            {
                bestScore = score;
                bestX = move.first;
                bestY = move.second;
            }
        }
    }
    else
    {
        int bestScore = numeric_limits<int>::max();

        for (auto move : moves)
        {
            State child = st;

            child.make_move(move.first, move.second);

            int score =
                alphabeta(child,
                          numeric_limits<int>::min(),
                          numeric_limits<int>::max());

            if (score < bestScore)
            {
                bestScore = score;
                bestX = move.first;
                bestY = move.second;
            }
        }
    }

    st.make_move(bestX, bestY);
}