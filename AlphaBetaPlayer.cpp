#include "AlphaBetaPlayer.h"

#include <limits>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

AlphaBetaPlayer::AlphaBetaPlayer(int depth)
{
    maxDepth = depth;
}

int AlphaBetaPlayer::alphabeta(State st, int depth, int alpha, int beta)
{
    stats.nodesVisited++;

    if(depth > stats.maxDepthReached)
    {
        stats.maxDepthReached = depth;
    }

    int winner = st.check_winner();

    // Victoria X
    if (winner == State::P1)
    {
        return 10000 - depth;
    }

    // Victoria O
    if (winner == State::P2)
    {
        return -10000 + depth;
    }

    // Empate
    if (st.full())
    {
        return 0;
    }

    // Corte por profundidad
    if (depth >= maxDepth)
    {
        return st.heuristic();
    }

    // MAX (X)
    if (st.get_to_move() == State::P1)
    {
        int value = numeric_limits<int>::min();

        for(auto move : st.legal_moves())
        {
            State child = st;

            child.make_move(move.first, move.second);

            value = max(value, alphabeta(child, depth + 1, alpha, beta));

            alpha = max(alpha, value);

            // poda beta
            if(alpha >= beta)
            {
                stats.nodesPruned++;
                break;
            }
        }

        return value;
    }

    // MIN (O)
    int value = numeric_limits<int>::max();

    for(auto move : st.legal_moves())
    {
        State child = st;

        child.make_move(move.first, move.second);

        value = min(value, alphabeta(child,depth + 1, alpha, beta));

        beta = min(beta, value);

        // poda alpha
        if(alpha >= beta)
        {
            stats.nodesPruned++;
            break;
        }
    }

    return value;
}

void AlphaBetaPlayer::play(State& st)
{
    stats.nodesVisited = 0;
    stats.nodesPruned = 0;
    stats.maxDepthReached = 0;
    stats.decisionTimeMs = 0;
    stats.memoryBytes = 0;

    auto start = chrono::high_resolution_clock::now();
    
    auto moves = st.legal_moves();

    if(moves.empty())
    {
        return;
    }

    pair<int,int> bestMove = moves[0];

    // X = MAX
    if(st.get_to_move() == State::P1)
    {
        int bestScore =
            numeric_limits<int>::min();

        for(auto move : moves)
        {
            State child = st;

            child.make_move(move.first, move.second);

            int score = alphabeta(child, 1, numeric_limits<int>::min(), numeric_limits<int>::max());

            if(score > bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }
    }

    // O = MIN
    else
    {
        int bestScore =
            numeric_limits<int>::max();

        for(auto move : moves)
        {
            State child = st;

            child.make_move(move.first,
                            move.second);

            int score = alphabeta(child, 1, numeric_limits<int>::min(), numeric_limits<int>::max());

            if(score < bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }
    }

    st.make_move(bestMove.first, bestMove.second);

    cout << "AlphaBeta juega: ("<< bestMove.first << ", "<< bestMove.second << ")" << endl;

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