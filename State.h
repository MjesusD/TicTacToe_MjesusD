#ifndef STATE_H
#define STATE_H

#include <array>
#include <string>
#include <vector>
#include <utility>

struct InputException { };

class State
{
public:

    enum Players { P2 = -1, P1 = 1 };

    static const int N = 3;
    static const int SIZE = N * N;

    static const std::array<char, 3> DISP;

    State();

    bool full() const;

    void set(const std::string & s);

    void print() const;

    bool make_move(int x, int y);

    int get_to_move() const;

    int check_winner() const;

    int get_square(int x, int y) const;

    std::vector<std::pair<int,int>> legal_moves() const;

private:

    int to_move;

    std::array<std::array<signed char, N>, N> sq;

    int filled;
};

#endif