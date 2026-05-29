#include "RandomPlayer.h"

#include <cstdlib>
#include <iostream>

using namespace std;

void RandomPlayer::play(State & st)
{
    while (true)
    {
        int x = rand() % 3;
        int y = rand() % 3;

        if (st.make_move(x, y))
        {
            cout << "Random juega: "
                 << x << " "
                 << y << endl;

            break;
        }
    }
}