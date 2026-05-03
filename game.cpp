#include "./game.h"
#include <iostream>

void printMenu() {
    std::cout << "-------------------------\n";
    std::cout << "     GAME RATINGS BOOK   \n";
    std::cout << "-------------------------\n\n";

    std::cout << "1. Add Game\n";
    std::cout << "2. Delete Game\n";
    std::cout << "3. View Games\n";
    std::cout << "4. Search Games\n";
    std::cout << "5. Sort Games\n";
    std::cout << "6. Load from File\n";
    std::cout << "7. Exit\n";

    std::cout << "Enter your choice: ";
}

void addGame(std::vector<Game>& games, int& nextId) {
    
}

void deleteGame(std::vector<Game>& games, int& nextId) {}

void viewGames(std::vector<Game>& games) {}

void searchGames(std::vector<Game>& games) {}

void sortGames(std::vector<Game>& games) {}

void saveToFile(const Game& game) {}

void loadFromFile(std::vector<Game>& games, int& nextId) {}