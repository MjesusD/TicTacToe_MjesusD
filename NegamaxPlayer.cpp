#include "NegamaxPlayer.h"

#include <limits>
#include <iostream>
#include <chrono>

using namespace std;

NegamaxPlayer::NegamaxPlayer(int depth)
{
    maxDepth = depth;
}

int NegamaxPlayer::negamax(State st, int depth)
{
    stats.nodesVisited++;

    if(depth > stats.maxDepthReached)
    {
        stats.maxDepthReached = depth;
    }

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
    stats.nodesVisited = 0;
    stats.nodesPruned = 0;
    stats.maxDepthReached = 0;
    stats.decisionTimeMs = 0;
    stats.memoryBytes = 0;

    auto start = chrono::high_resolution_clock::now();

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

    auto end = chrono::high_resolution_clock::now();

    stats.decisionTimeMs = chrono::duration<double, milli>(end - start).count();

    stats.memoryBytes = stats.nodesVisited * sizeof(State);

    totalStats.nodesVisited += stats.nodesVisited;

    totalStats.nodesPruned += stats.nodesPruned;

    totalStats.decisionTimeMs += stats.decisionTimeMs;

    totalStats.memoryBytes += stats.memoryBytes;

    if(stats.maxDepthReached >
    totalStats.maxDepthReached)
    {
        totalStats.maxDepthReached =
            stats.maxDepthReached;
    }

}