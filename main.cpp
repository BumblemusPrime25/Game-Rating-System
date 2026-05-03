#include "./game.h"
#include <iostream>
#include <filesystem>
#include <vector>

int main() {
    std::vector<Game> games;

    int nextId = 1;

    std::string path = "ratings.txt";
    if (std::filesystem::exists(path)) {
        loadFromFile(games, nextId);
    }

    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addGame(games, nextId);
                break;

            case 2:
                deleteGame(games, nextId);
                break;

            case 3:
                viewGames(games);
                break;

            case 4:
                searchGames(games);
                break;

            case 5:
                sortGames(games);
                break;

            case 6:
                std::cout << "Exiting program...\n";
                return 0;

            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    }

    return 0;
}