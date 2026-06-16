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
#include <fstream>

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

    ofstream report("resultados.csv", ios::app);

    if(!report)
    {
        cout << "Error al abrir resultados.csv" << endl;
        return 1;
    }

    if(report.tellp() == 0)
{
    report
    << "JugadorX,"
    << "JugadorO,"
    << "Resultado,"
    << "Turnos,"
    << "Ancho,"
    << "Alto,"
    << "K,"
    << "H,"
    << "NodosX,"
    << "PodasX,"
    << "ProfundidadX,"
    << "TiempoX,"
    << "MemoriaX,"
    << "NodosO,"
    << "PodasO,"
    << "ProfundidadO,"
    << "TiempoO,"
    << "MemoriaO"
    << endl;
}

    string result;
    int turns = 0;
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

    string playerXName;
    string playerOName;

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
            playerXName = "Humano";
            break;

        case 2:
            playerX = new RandomPlayer();
            playerXName = "Random";
            break;

        case 3:
            playerX = new MinimaxPlayer(H);
            playerXName = "MinMax";
            break;

        case 4:
            playerX = new NegamaxPlayer(H);
            playerXName = "NegaMax";
            break;

        case 5:
            playerX = new AlphaBetaPlayer(H);
            playerXName = "AlphaBeta";
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
            playerOName = "Humano";
            break;

        case 2:
            playerO = new RandomPlayer();
            playerOName = "Random";
            break;

        case 3:
            playerO = new MinimaxPlayer(H);
            playerOName = "MinMax";
            break;

        case 4:
            playerO = new NegamaxPlayer(H);
            playerOName = "NegaMax";
            break;

        case 5:
            playerO = new AlphaBetaPlayer(H);
            playerOName = "AlphaBeta";
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
            result = "Gana X";
            cout << result << endl;
            break;
        }

        if (winner == State::P2)
        {
            result = "Gana O";
            cout << result << endl;
            break;
        }

        if (st.full())
        {
            result = "Empate";
            cout << result << endl;
            break;
        }

        if (st.get_to_move() == State::P1)
        {
            cout << "Turno X" << endl;
            playerX->play(st);
            turns++;
        }
        else
        {
            cout << "Turno O" << endl;
            playerO->play(st);
            turns++;
        }
    }

    // Obtener estadísticas 
    SearchStats statsX = playerX->getStats();
    SearchStats statsO = playerO->getStats();

    cout << "\n========================" << endl;
    cout << "RESULTADOS FINALES" << endl;
    cout << "========================" << endl;

    cout << "Resultado: "
         << result << endl;

    cout << "Turnos jugados: "
         << turns << endl;

    cout << "\n--- Jugador X ---" << endl;

    cout << "Nodos visitados: "
         << statsX.nodesVisited << endl;

    cout << "Nodos podados: "
         << statsX.nodesPruned << endl;

    cout << "Profundidad maxima: "
         << statsX.maxDepthReached << endl;

    cout << "Tiempo total (ms): "
         << statsX.decisionTimeMs << endl;

    cout << "Memoria estimada (bytes): "
         << statsX.memoryBytes << endl;

    cout << "\n--- Jugador O ---" << endl;

    cout << "Nodos visitados: "
         << statsO.nodesVisited << endl;

    cout << "Nodos podados: "
         << statsO.nodesPruned << endl;

    cout << "Profundidad maxima: "
         << statsO.maxDepthReached << endl;

    cout << "Tiempo total (ms): "
         << statsO.decisionTimeMs << endl;

    cout << "Memoria estimada (bytes): "
         << statsO.memoryBytes << endl;


    report
    << playerXName << ","
    << playerOName << ","
    << result << ","
    << turns << ","
    << width << ","
    << height << ","
    << k << ","
    << H << ","

    << statsX.nodesVisited << ","
    << statsX.nodesPruned << ","
    << statsX.maxDepthReached << ","
    << statsX.decisionTimeMs << ","
    << statsX.memoryBytes << ","

    << statsO.nodesVisited << ","
    << statsO.nodesPruned << ","
    << statsO.maxDepthReached << ","
    << statsO.decisionTimeMs << ","
    << statsO.memoryBytes

    << endl;

    report.close();

    delete playerX;
    delete playerO;

    return 0;
}