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
        system("start chrome https://chromedino.com/");
    }
    else if (name == "2048")
    {
        system("start chrome https://play2048.co/");
    }
    else if (name == "FlappyBird")
    {
        system("start chrome https://flappybird.io/");
    }
    else if (name == "pacman")
    {
        system("start chrome https://freepacman.org/");
    }
    else if (name == "minesweeper")
    {
        system("start chrome https://minesweeperonline.com/");
    }
    else if (name == "supermario")
    {
        system("start chrome https://supermario-game.com/vi");
    }
}