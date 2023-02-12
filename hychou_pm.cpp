#include <iostream>
#include <vector>
#include "hychou_pm.h"

PM::PM() {}

int PM::Core()
{
    damage = new int *[N];
    color = new char *[N];
    parent = new char *[N];
    for (int i = 0; i < N; ++i)
    {
        damage[i] = new int[N];
        color[i] = new char[N];
        parent[i] = new char[N];
        for (int j = 0; j < N; ++j)
        {
            damage[i][j] = -1;
            color[i][j] = '|';
        }
    }

    color[0][0] = '-';
    parent[0][0] = 'O';
    damage[0][0] = poison[0][0];
    goForward();
    int C = damage[N - 1][N - 1];
    goBack(N - 1, N - 1);

    for (int i = 0; i < N; ++i)
    {
        delete[] parent[i];
        delete[] color[i];
        delete[] damage[i];
    }
    delete[] parent;
    delete[] color;
    delete[] damage;

    return (C);
}

void PM::goForward()
{
    bool found = false;
    int minx, miny, mind;

    for (int i = 0; i < N && !found; ++i)
    {
        for (int j = 0; j < N && !found; ++j)
        {
            if (color[i][j] == '-')
            {
                minx = j;
                miny = i;
                mind = damage[i][j];
                found = true;
            }
        }
    }
    if (!found || (minx == N && miny == N))
        return;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (color[i][j] == '-' && damage[i][j] < mind)
            {
                minx = j;
                miny = i;
                mind = damage[i][j];
            }
        }
    }

    color[miny][minx] = '=';
    relax(miny - 1, minx, 'U');
    relax(miny + 1, minx, 'D');
    relax(miny, minx - 1, 'L');
    relax(miny, minx + 1, 'R');

    goForward();
}

void PM::relax(int y, int x, char p)
{
    if (x < 0 || N <= x || y < 0 || N <= y)
        return;

    int pshere = poison[y][x];

    if (color[y][x] == '|')
    {
        color[y][x] = '-';
        parent[y][x] = p;
        if (p == 'U')
            damage[y][x] = damage[y + 1][x] + pshere;
        else if (p == 'D')
            damage[y][x] = damage[y - 1][x] + pshere;
        else if (p == 'L')
            damage[y][x] = damage[y][x + 1] + pshere;
        else if (p == 'R')
            damage[y][x] = damage[y][x - 1] + pshere;
    }
    else if (color[y][x] == '-')
    {
        if (p == 'U')
        {
            if (damage[y][x] > damage[y + 1][x] + pshere)
            {
                damage[y][x] = damage[y + 1][x] + pshere;
                parent[y][x] = p;
            }
        }
        else if (p == 'D')
        {
            if (damage[y][x] > damage[y - 1][x] + pshere)
            {
                damage[y][x] = damage[y - 1][x] + pshere;
                parent[y][x] = p;
            }
        }
        else if (p == 'L')
        {
            if (damage[y][x] > damage[y][x + 1] + pshere)
            {
                damage[y][x] = damage[y][x + 1] + pshere;
                parent[y][x] = p;
            }
        }
        else if (p == 'R')
        {
            if (damage[y][x] > damage[y][x - 1] + pshere)
            {
                damage[y][x] = damage[y][x - 1] + pshere;
                parent[y][x] = p;
            }
        }
    }
}

void PM::goBack(int y, int x)
{
    char p = parent[y][x];

    if (p == 'O')
        return;

    route.push_back(p);
    if (p == 'U')
        goBack(y + 1, x);
    else if (p == 'D')
        goBack(y - 1, x);
    else if (p == 'L')
        goBack(y, x + 1);
    else if (p == 'R')
        goBack(y, x - 1);

    parent[y][x] = '*';
}