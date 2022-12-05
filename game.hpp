#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <memory>

class game
{
private:
    int width;
    int height;
    bool minesGenerated;
    std::unique_ptr<std::unique_ptr<std::unique_ptr<int>[]>[]> truth;
    std::unique_ptr<std::unique_ptr<std::unique_ptr<int>[]>[]> displayed;
public:
    game(int, int);
    int hit(int X, int Y, int numMines);
    int flag(int x, int y);
    int autoHit(int x, int y);
    void neighboringMines();
    void generateMines(int numMines, int excludeX, int excludeY);
    int checkWin();
    void revealAll();
    friend std::ostream &operator<<(std::ostream &os, const game &g);
};

#endif
