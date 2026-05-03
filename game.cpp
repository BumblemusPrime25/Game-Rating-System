#include "./game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

void printMenu() {
    std::cout << "-------------------------\n";
    std::cout << "     GAME RATINGS BOOK   \n";
    std::cout << "-------------------------\n\n";

    std::cout << "1. Add Game\n";
    std::cout << "2. View Games\n";
    std::cout << "3. Search Games\n";
    std::cout << "4. Sort Games\n";
    std::cout << "5. Load from File\n";
    std::cout << "6. Exit\n";

    std::cout << "Enter your choice: ";
}

void addGame(std::vector<Game>& games, int& nextId) {
    Game game;

    std::string name;
    std::string description;
    int grade;
    int id;

    std::cout << "ENTER GAME NAME: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);

    std::cout << "ENTER GAME DESCRIPTION: ";
    std::getline(std::cin, description);

    while (true) {
        std::cout << "ENTER RATING (0-100): ";
        std::cin >> grade;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cout << "INVALID INPUT. PLEASE ENTER A NUMBER.\n";
            continue;
        }

        if (grade < 0 || grade > 100) {
            std::cout << "INVALID RATING. MUST BE 0-100.\n";
        } else {
            break;
        }
    }

    id = nextId;
    nextId++;

    game.title = name;
    game.description = description;
    game.rating = grade;
    game.id = id;

    games.push_back(game);
    std::cout << "GAME ADDED SUCCESSFULLY!\n";

    saveToFile(game);
}

void viewGames(std::vector<Game>& games) {
    for (size_t i = 0; i < games.size(); ++i) {
        std::cout << "ID: " << games[i].id
                  << ", Title: " << games[i].title
                  << ", Rating: " << games[i].rating
                  << ", Description: " << games[i].description
                  << std::endl;
    }
}

void searchGames(std::vector<Game>& games) {
    std::string search;

    std::cout << "Enter game you want to search: ";
    std::cin >> search;

    std::ifstream file("games.txt");
    std::string line;

    int lineNumber = 0;

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        lineNumber++;

        if (line.find(search) != std::string::npos) {

            std::stringstream ss(line);
            std::string idStr, nameStr, gradeStr, descStr;

            std::getline(ss, idStr, ',');
            std::getline(ss, nameStr, ',');
            std::getline(ss, gradeStr, ',');
            std::getline(ss, descStr, ',');

            std::cout << "Found game on line " << lineNumber << ":\n";
            std::cout << "  ID: " << idStr << "\n";
            std::cout << "  Name: " << nameStr << "\n";
            std::cout << "  Rating: " << gradeStr << "\n";
            std::cout << "  Description: " << descStr << "\n\n";
        }
    }

    std::string search;

    std::cout << "Enter game you want to search: ";
    std::cin >> search;

    std::ifstream file("ratings.txt");
    std::string line;

    int lineNumber = 0;

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        lineNumber++;

        if (line.find(search) != std::string::npos) {

            std::stringstream ss(line);
            std::string idStr, nameStr, gradeStr, descStr;

            std::getline(ss, idStr, ',');
            std::getline(ss, nameStr, ',');
            std::getline(ss, gradeStr, ',');
            std::getline(ss, descStr, ',');

            std::cout << "Found game on line " << lineNumber << ":\n";
            std::cout << "  ID: " << idStr << "\n";
            std::cout << "  Name: " << nameStr << "\n";
            std::cout << "  Rating: " << gradeStr << "\n";
            std::cout << "  Description: " << descStr << "\n\n";
        }        
    }
}

void sortGames(std::vector<Game>& games) {
    int choice;

    std::cout << "\nSort by:\n";
    std::cout << "1. ID\n";
    std::cout << "2. Name\n";
    std::cout << "3. Rating\n";
    std::cout << "Enter choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::sort(games.begin(), games.end(),
                [](const Game& a, const Game& b) {
                    return a.id < b.id;
                }
            );
            std::cout << "Sorted by ID.\n";
            break;

        case 2:
            std::sort(games.begin(), games.end(),
                [](const Game& a, const Game& b) {
                    return a.title < b.title;
                }
            );
            std::cout << "Sorted by Name.\n";
            break;

        case 3:
            std::sort(games.begin(), games.end(),
                [](const Game& a, const Game& b) {
                    return a.rating > b.rating;
                }
            );
            std::cout << "Sorted by Rating.\n";
            break;

        default:
            std::cout << "Invalid choice.\n";
            return;
    }

    std::cout << "Games sorted successfully!\n";
}

void saveToFile(const Game& game) {
    std::ofstream gamesFile("ratings.txt", std::ios::app);

    if (!gamesFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return;
    }

    gamesFile << game.id << ","
              << game.title << ","
              << game.rating << ","
              << game.description << "\n";
}

void loadFromFile(std::vector<Game>& games, int& nextId) {
    std::ifstream file("ratings.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open ratings.txt for reading.\n";
        return;
    }

    games.clear();
    nextId = 1;

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string idStr, nameStr, gradeStr, descStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, nameStr, ',');
        std::getline(ss, gradeStr, ',');
        std::getline(ss, descStr, ',');

        int id = std::stoi(idStr);
        int grade = std::stoi(gradeStr);

        Game game;
        game.id = id;
        game.title = nameStr;
        game.rating = grade;
        game.description = descStr;

        games.push_back(game);

        if (id >= nextId) {
            nextId = id + 1;
        }
    }

    file.close();
    std::cout << "Games loaded successfully!\n";
}