// minesweeper game
#include "game.hpp"

#include <memory>
#include <iostream>
#include <iomanip>
#include "random.hpp"

using namespace std;

game::game(int width, int height) : width{width},
                                    height{height},
                                    minesGenerated{false},
                                    truth{make_unique<unique_ptr<unique_ptr<int>[]>[]>(width)},
                                    displayed{make_unique<unique_ptr<unique_ptr<int>[]>[]>(width)}
{
    // set up each column
    for (int i{0}; i < width; ++i)
    {
        truth[i] = make_unique<unique_ptr<int>[]>(height);
        displayed[i] = make_unique<unique_ptr<int>[]>(height);

        for (int j{0}; j < height; ++j)
        {
            truth[i][j] = make_unique<int>(0);
            displayed[i][j] = make_unique<int>(-2);
            // -3 flagged, -2 unrevealed, -1 is bomb, 0-8 is number of neighboring bombs
        }
    }
}

void game::generateMines(int numMines, int excludeX, int excludeY)
{
    auto locations = randomMineLocations(width, height, excludeX, excludeY, numMines);

    // mines
    for (int i{0}; i < numMines; ++i)
    {
        int x = locations[i].first;
        int y = locations[i].second;
        *truth[x][y] = -1;
    }
}

void game::neighboringMines()
{
    int dx[] = {1, -1, 0, 0, 1, -1, 1, -1};
    int dy[] = {0, 0, 1, -1, 1, -1, -1, 1};
    // mines
    for (int i{0}; i < width; ++i)
    {
        for (int j{0}; j < height; ++j)
        {
            if (*truth[i][j] != -1)
            {
                for (int k{0}; k < 8; ++k)
                {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < width && y >= 0 && y < height)
                    {
                        if (*truth[x][y] == -1)
                        {
                            *truth[i][j] += 1;
                        }
                    }
                }
            }
        }
    }
}

int game::hit(int x, int y, int numMines)
{

    int dx[] = {1, -1, 0, 0, 1, -1, 1, -1};
    int dy[] = {0, 0, 1, -1, 1, -1, -1, 1};
    if (!minesGenerated)
    {
        generateMines(numMines, x, y);
        neighboringMines();
        minesGenerated = true;
    }

    // hit a mine
    if (*truth[x][y] == -1)
    {
        revealAll();
        return 1;
    }
    else
    {
        // make sure it hasn't been hit
        if (*displayed[x][y] >= 0)
        {
            return 0;
        }
        // didn't hit a mine, needs to reveal itself and then all neighboring cells/associated numbers of 0-adjacent cells

        // revealing the mine means changing display to the true value
        *displayed[x][y] = *truth[x][y];

        // reveal all neighboring cells (of 0 adjacent bombs) recursively
        if (*truth[x][y] == 0)
        {
            for (int i{0}; i < 8; ++i)
            {
                int x1 = x + dx[i];
                int y1 = y + dy[i];
                if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
                {
                    // not a bomb and unrevealed
                    if ((*truth[x1][y1] != -1) && (*displayed[x1][y1] <= -2))
                    {
                        hit(x1, y1, numMines);
                    }
                }
            }
        }
        return 0;
    }
}

int game::flag(int x, int y)
{
    if (*displayed[x][y] >= 0)
    {
        return 0; // failed to flag
    }
    if (*displayed[x][y] == -3)
    {
        *displayed[x][y] = -2; // unflagged
    }
    else
    {
        *displayed[x][y] = -3; // flagged
    }
    return 1; // success
}

int game::autoHit(int x, int y)
{
    if (*displayed[x][y] <= -2)
    {
        return 0;
    }
    int dx[] = {1, -1, 0, 0, 1, -1, 1, -1};
    int dy[] = {0, 0, 1, -1, 1, -1, -1, 1};
    int numFlags = 0;
    for (int i{0}; i < 8; ++i)
    {
        int x1 = x + dx[i];
        int y1 = y + dy[i];
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
        {
            if (*displayed[x1][y1] == -3)
            {
                numFlags++;
            }
        }
    }
    if (numFlags == *truth[x][y])
    {
        for (int i{0}; i < 8; ++i)
        {
            int x1 = x + dx[i];
            int y1 = y + dy[i];
            if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
            {
                if (*displayed[x1][y1] == -2)
                {
                    hit(x1, y1, 0);
                }
            }
        }
        return 1; // succeeded
    }
    return 0; // failed to auto hit
}

void game::revealAll()
{
    for (int i{0}; i < width; ++i)
    {
        for (int j{0}; j < height; ++j)
        {
            *displayed[i][j] = *truth[i][j];
        }
    }
}

int game::checkWin()
{
    for (int i{0}; i < width; ++i)
    {
        for (int j{0}; j < height; ++j)
        {
            // game is not yet won if any cell that is not a mine is unrevealed
            if (*truth[i][j] != -1 && *displayed[i][j] <= -2)
            {
                return 0;
            }
        }
    }
    revealAll();
    return 1;
}

ostream &operator<<(ostream &os, const game &g)
{
    // first print the top row of x coordinates
    os << setw(3) << " "; // leave a space for the column of y coordinate labels
    for (int i{0}; i < g.width; ++i)
    {
        // setw sets the width of the next thing to be printed
        os << setw(3) << i + 1;
    }
    os << "\n";

    // print row by row
    for (int i{0}; i < g.height; ++i)
    {
        // first print the y coordinate
        os << setw(3) << i + 1;
        for (int j{0}; j < g.width; ++j)
        {
            // print the value of the cell
            if (*g.displayed[j][i] == -3)
            {
                os << setw(3) << "P";
            }
            else if (*g.displayed[j][i] == -2)
            {
                os << setw(3) << ".";
            }
            else if (*g.displayed[j][i] == -1)
            {
                os << setw(3) << "*";
            }
            else if (*g.displayed[j][i] == 0)
            {
                os << setw(3) << " ";
            }
            else
            {
                os << setw(3) << *g.displayed[j][i];
            }
        }

        os << "\n";
    }
    return os;
}
