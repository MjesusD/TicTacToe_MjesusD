#include "State.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void clear_screen()
{
    // Linux 
    system("clear");

    // Windows:
    // system("cls");
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
    cout << "Opción: ";

    cin >> option;

    if (option == 1)
    {
        playerX = new HumanPlayer();
    }
    else
    {
        playerX = new RandomPlayer();
    }

    cout << endl;

    cout << "=== Selección jugador O ===" << endl;
    cout << "1. Humano" << endl;
    cout << "2. Aleatorio" << endl;
    cout << "Opción: ";

    cin >> option;

    if (option == 1)
    {
        playerO = new HumanPlayer();
    }
    else
    {
        playerO = new RandomPlayer();
    }

    // Ciclo del juego

    while (true)
    {
        clear_screen();

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