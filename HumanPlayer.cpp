#include "HumanPlayer.h"

#include <iostream>
#include <limits>

using namespace std;

void HumanPlayer::play(State & st)
{
    while (true)
    {
        int x, y;

        cout << "Ingrese x y: ";

        if (!(cin >> x >> y))
        {
            cout << "Entrada invalida. Debe ingresar numeros." << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        if (x < 0 || x >= st.get_width() ||
            y < 0 || y >= st.get_height())
        {
            cout << "Posicion fuera de rango." << endl;
            continue;
        }

        if (!st.make_move(x, y))
        {
            cout << "Casilla ocupada." << endl;
            continue;
        }

        break;
    }
}