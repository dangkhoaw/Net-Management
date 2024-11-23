#ifndef GAME
#define GAME 1

#include <iostream>

using namespace std;

class Game
{
private:
    string name;

public:
    Game(string name = "");
    ~Game();

    string getName();
    void setName(string name);

    friend ostream &operator<<(ostream &os, const Game &game);
    friend istream &operator>>(istream &is, Game &game);

    void playGame();
};

#endif