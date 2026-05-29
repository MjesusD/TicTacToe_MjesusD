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

        // validar entrada númerica
        if (!(cin >> x >> y))
        {
            cout << "Entrada inválida. Debe ingresar números." << endl;

            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        // validar rango
        if (x < 0 || x >= 3 || y < 0 || y >= 3)
        {
            cout << "Posición fuera de rango." << endl;

            continue;
        }

        // validar casilla libre
        if (!st.make_move(x, y))
        {
            cout << "Casilla ocupada." << endl;

            continue;
        }

        break;
    }
}