#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
#include <utility>

struct InputException { };

class State
{
public:

    enum Players { P2 = -1, P1 = 1 };

    State(int width, int height, int k);

    bool full() const;

    void print() const;

    bool make_move(int x, int y);

    int get_to_move() const;

    int check_winner() const;

    int get_square(int x, int y) const;

    std::vector<std::pair<int,int>> legal_moves() const;

    int heuristic() const;

    // Nuevos getters
    int get_width() const;
    int get_height() const;
    int get_k() const;

private:

    int width;
    int height;
    int k;

    int to_move;

    std::vector<std::vector<signed char>> sq;

    int filled;
};

#endif