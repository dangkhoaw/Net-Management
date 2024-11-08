#include "game.h"

Game::Game(string name) : name(name) {}

Game::~Game() {}

string Game::getName() { return name; }

void Game::setName(string name) { this->name = name; }

ostream &operator<<(ostream &os, const Game &game)
{
    os << game.name;
    return os;
}

istream &operator>>(istream &is, Game &game)
{
    is >> game.name;
    return is;
}

void Game::playGame()
{
    if (name == "T-Rex Dinosaurs")
    {
        system("start msedge https://chromedino.com/");
    }
    else if (name == "2048")
    {
        system("start msedge https://play2048.co/");
    }
    else if (name == "FlappyBird")
    {
        system("start msedge https://flappybird.io/");
    }
    else if (name == "pacman")
    {
        system("start msedge https://freepacman.org/");
    }
    else if (name == "minesweeper")
    {
        system("start msedge https://minesweeperonline.com/");
    }
    else if (name == "supermario")
    {
        system("start msedge https://supermario-game.com/vi");
    }
}