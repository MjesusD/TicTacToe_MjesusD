#include "State.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

const array<char, 3> State::DISP = {{ 'o', '-', 'x' }};

State::State()
{
    sq = { {} };
    to_move = P1;
    filled = 0;
}

bool State::full() const
{
    return filled >= SIZE;
}

void State::set(const string & s)
{
    istringstream is(s);

    char c;

    to_move = P1;
    filled = 0;

    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < N; ++x)
        {
            is >> c;

            if (!is)
            {
                throw InputException();
            }

            if (c == DISP[1 + P1])
            {
                sq[y][x] = P1;
                ++filled;
            }
            else if (c == DISP[1 + P2])
            {
                sq[y][x] = P2;
                ++filled;
            }
            else
            {
                sq[y][x] = 0;
            }
        }
    }

    is >> c;

    if (is)
    {
        throw InputException();
    }
}

void State::print() const
{
    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < N; ++x)
        {
            cout << DISP[sq[y][x] + 1];
        }

        cout << endl;
    }

    cout << DISP[to_move + 1]
         << " (" << filled << ")"
         << endl;
}

bool State::make_move(int x, int y)
{
    assert(x >= 0 && x < N && y >= 0 && y < N);

    auto & c = sq[y][x];

    if (c)
    {
        return false;
    }

    c = to_move;

    to_move = -to_move;

    ++filled;

    return true;
}

int State::get_to_move() const
{
    return to_move;
}

int State::check_winner() const
{
    // filas
    for (int y = 0; y < N; ++y)
    {
        int sum = sq[y][0] + sq[y][1] + sq[y][2];

        if (sum == 3) return P1;
        if (sum == -3) return P2;
    }

    // columnas
    for (int x = 0; x < N; ++x)
    {
        int sum = sq[0][x] + sq[1][x] + sq[2][x];

        if (sum == 3) return P1;
        if (sum == -3) return P2;
    }

    // diagonales
    int diag1 = sq[0][0] + sq[1][1] + sq[2][2];

    if (diag1 == 3) return P1;
    if (diag1 == -3) return P2;

    int diag2 = sq[0][2] + sq[1][1] + sq[2][0];

    if (diag2 == 3) return P1;
    if (diag2 == -3) return P2;

    return 0;
}