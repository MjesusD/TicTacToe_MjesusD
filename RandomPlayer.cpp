#include "RandomPlayer.h"

#include <cstdlib>
#include <iostream>

using namespace std;

void RandomPlayer::play(State & st)
{
    auto moves = st.legal_moves();

    int pos = rand() % moves.size();

    int x = moves[pos].first;
    int y = moves[pos].second;

    st.make_move(x, y);

    cout << "Random juega: "
         << x << " "
         << y << endl;
}