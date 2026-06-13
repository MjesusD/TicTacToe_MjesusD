#include "State.h"

#include <iostream>

using namespace std;

State::State(int w, int h, int kvalue)
{
    width = w;
    height = h;
    k = kvalue;

    sq.resize(height);

    for(int y = 0; y < height; y++)
    {
        sq[y].resize(width, 0);
    }

    to_move = P1;
    filled = 0;
}

bool State::full() const
{
    return filled >= width * height;
}

void State::print() const
{
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(sq[y][x] == P1)
            {
                cout << "X ";
            }
            else if(sq[y][x] == P2)
            {
                cout << "O ";
            }
            else
            {
                cout << "- ";
            }
        }

        cout << endl;
    }

    cout << endl;
}

bool State::make_move(int x, int y)
{
    if(x < 0 || x >= width)
    {
        return false;
    }

    if(y < 0 || y >= height)
    {
        return false;
    }

    if(sq[y][x] != 0)
    {
        return false;
    }

    sq[y][x] = to_move;

    to_move = -to_move;

    filled++;

    return true;
}

int State::get_to_move() const
{
    return to_move;
}

int State::get_square(int x, int y) const
{
    return sq[y][x];
}

std::vector<std::pair<int,int>> State::legal_moves() const
{
    vector<pair<int,int>> moves;

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(sq[y][x] == 0)
            {
                moves.push_back({x,y});
            }
        }
    }

    return moves;
}

int State::check_winner() const
{
    // Direcciones:
    // horizontal
    // vertical
    // diagonal principal
    // diagonal secundaria

    int dx[4] = {1, 0, 1, 1};
    int dy[4] = {0, 1, 1, -1};

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int player = sq[y][x];

            if(player == 0)
            {
                continue;
            }

            for(int dir = 0; dir < 4; dir++)
            {
                int count = 1;

                for(int step = 1; step < k; step++)
                {
                    int nx = x + dx[dir] * step;
                    int ny = y + dy[dir] * step;

                    if(nx < 0 || nx >= width)
                    {
                        break;
                    }

                    if(ny < 0 || ny >= height)
                    {
                        break;
                    }

                    if(sq[ny][nx] != player)
                    {
                        break;
                    }

                    count++;
                }

                if(count >= k)
                {
                    return player;
                }
            }
        }
    }

    return 0;
}

int State::heuristic() const
{
    int scoreX = 0;
    int scoreO = 0;

    int dx[4] = {1, 0, 1, 1};
    int dy[4] = {0, 1, 1, -1};

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int player = sq[y][x];

            if(player == 0)
            {
                continue;
            }

            for(int dir = 0; dir < 4; dir++)
            {
                // Verificar si esta casilla es el inicio de la línea
                int px = x - dx[dir];
                int py = y - dy[dir];

                if(px >= 0 &&
                   px < width &&
                   py >= 0 &&
                   py < height &&
                   sq[py][px] == player)
                {
                    continue;
                }

                int count = 1;

                int nx = x + dx[dir];
                int ny = y + dy[dir];

                while(nx >= 0 &&
                      nx < width &&
                      ny >= 0 &&
                      ny < height &&
                      sq[ny][nx] == player)
                {
                    count++;

                    nx += dx[dir];
                    ny += dy[dir];
                }

                int value = count * count;

                if(player == P1)
                {
                    scoreX += value;
                }
                else
                {
                    scoreO += value;
                }
            }
        }
    }

    return scoreX - scoreO;
}

int State::get_width() const
{
    return width;
}

int State::get_height() const
{
    return height;
}

int State::get_k() const
{
    return k;
}