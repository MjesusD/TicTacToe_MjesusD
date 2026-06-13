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

    int width;
    int height;
    int k;
    int H;

    cout << "=== Configuracion del tablero ===" << endl;

    cout << "Ancho: ";
    cin >> width;

    cout << "Alto: ";
    cin >> height;

    cout << "K (fichas consecutivas para ganar): ";
    cin >> k;

    cout << "Profundidad de busqueda (H): ";
    cin >> H;

    State st(width, height, k);

    Player* playerX = nullptr;
    Player* playerO = nullptr;

    int option;

    cout << endl;
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
            playerX = new MinimaxPlayer(H);
            break;

        case 4:
            playerX = new NegamaxPlayer(H);
            break;

        case 5:
            playerX = new AlphaBetaPlayer(H);
            break;

        default:
            cout << "Opcion invalida" << endl;
            return 1;
    }

    cout << endl;

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
            playerO = new HumanPlayer();
            break;

        case 2:
            playerO = new RandomPlayer();
            break;

        case 3:
            playerO = new MinimaxPlayer(H);
            break;

        case 4:
            playerO = new NegamaxPlayer(H);
            break;

        case 5:
            playerO = new AlphaBetaPlayer(H);
            break;

        default:
            cout << "Opcion invalida" << endl;
            return 1;
    }

    while (true)
    {

        //clear_screen();
        cout << endl;
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
            cout << "Turno X" << endl;
            playerX->play(st);
        }
        else
        {
            cout << "Turno O" << endl;
            playerO->play(st);
        }
    }

    delete playerX;
    delete playerO;

    return 0;
}