#ifndef GAME_H
#define GAME_H
#include <iostream>

struct Game
{
    int id;
    std::string title;
    std::string description;
    int rating;
};

void printMenu();

void addGame(std::vector<Game>& games, int& nextId);

void deleteGame(std::vector<Game>& games, int& nextId);

void viewGames(std::vector<Game>& games);

void searchGames(std::vector<Game>& games);

void sortGames(std::vector<Game>& games);

void saveToFile(const Game& game);

void loadFromFile(std::vector<Game>& games, int& nextId);

#endif