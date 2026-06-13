#include "State.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "MinimaxPlayer.h"
#include "NegamaxPlayer.h"
#include "AlphaBetaPlayer.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    srand(time(0));

    State st;

    Player* playerX;
    Player* playerO;

    int option;

    cout << "=== Selección jugador X ===" << endl;
    cout << "1. Humano" << endl;
    cout << "2. Aleatorio" << endl;
    cout << "3. Minimax" << endl;
    cout << "4. Negamax" << endl;
    cout << "5. AlphaBeta" << endl;
    cout << "Opción: ";

    cin >> option;

    switch(option)
{
    case 1:
        playerX = new HumanPlayer();
        break;

    case 2:
        playerX = new RandomPlayer();
        break;

    case 3:
        playerX = new MinimaxPlayer();
        break;

    case 4:
        playerX = new NegamaxPlayer();
        break;

    case 5:
        playerX = new AlphaBetaPlayer();
        break;

    default:
        cout << "Opcion invalida" << endl;
        return 1;
}

    cout << endl;

    cout << "=== Selección jugador O ===" << endl;
    cout << "1. Humano" << endl;
    cout << "2. Aleatorio" << endl;
    cout << "3. Minimax" << endl;
    cout << "4. Negamax" << endl;
    cout << "5. AlphaBeta" << endl;
    cout << "Opción: ";

    cin >> option;

    switch(option)
{
    case 1:
        playerO = new HumanPlayer();
        break;

    case 2:
        playerO = new RandomPlayer();
        break;

    case 3:
        playerO = new MinimaxPlayer();
        break;

    case 4:
        playerO = new NegamaxPlayer();
        break;

    case 5:
        playerO = new AlphaBetaPlayer();
        break;

    default:
        cout << "Opcion invalida" << endl;
        return 1;
}

    // Ciclo del juego

    while (true)
    {
        //clear_screen();

        cout << "=== TIC TAC TOE ===" << endl;

        st.print();

        int winner = st.check_winner();

        if (winner == State::P1)
        {
            cout << "Gana X" << endl;
            break;
        }

        if (winner == State::P2)
        {
            cout << "Gana O" << endl;
            break;
        }

        if (st.full())
        {
            cout << "Empate" << endl;
            break;
        }

        if (st.get_to_move() == State::P1)
        {
            cout << endl;
            cout << "Turno X" << endl;

            playerX->play(st);
        }
        else
        {
            cout << endl;
            cout << "Turno O" << endl;

            playerO->play(st);
        }
    }

    delete playerX;
    delete playerO;

    return 0;
}