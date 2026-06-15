#ifndef SEARCHSTATS_H
#define SEARCHSTATS_H

struct SearchStats
{
    long long nodesVisited = 0;
    long long nodesPruned = 0;
    long long memoryBytes = 0;

    int maxDepthReached = 0;

    double decisionTimeMs = 0.0;
};

#endif