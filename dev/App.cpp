#include "App.h"
#include <iostream>
#include <string>
#include <fstream>

App::App(std::string apiKey) : apiClient(apiKey) {
    loadHistory(); // Load search history from file on startup
}

App::~App() {
    saveHistory(); // Save search history to file before exit
    clearHistory(); // Ensure we delete dynamically allocated movies when App is destroyed
}

void App::run() {
    int choice = 0;
    while (choice != 4) {
        std::cout << "\n=== Movie Information Fetcher ===\n";
        std::cout << "1. Search for a Movie\n";
        std::cout << "2. View Search History\n";
        std::cout << "3. Clear History\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                std::cout << "\nDetected end-of-file. Exiting.\n";
                break;
            }
            std::cout << "Invalid choice. Please enter a valid menu number (1-4).\n";
            std::cin.clear(); // Clear the error state
            std::cin.ignore(10000, '\n'); // Clear the rest of the line
            continue; // Re-prompt
        }
        std::cin.ignore(10000, '\n'); // Clear newline and any trailing garbage from buffer

        switch (choice) {
            case 1:
                searchMovie();
                break;
            case 2:
                viewHistory();
                break;
            case 3:
                clearHistory(true);
                std::cout << "History cleared.\n";
                break;
            case 4:
                std::cout << "Exiting program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void App::searchMovie() {
    std::cout << "\nEnter movie title: ";
    std::string title;
    std::getline(std::cin, title);

    // Validate and trim whitespace
    std::string trimmed = title;
    size_t start = trimmed.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        std::cout << "Error: Movie title cannot be empty.\n";
        return;
    }
    size_t end = trimmed.find_last_not_of(" \t\r\n");
    trimmed = trimmed.substr(start, end - start + 1);

    std::cout << "Fetching data...\n";
    Movie* newMovie = apiClient.fetchMovie(trimmed);

    if (newMovie != nullptr) {
        newMovie->display();
        searchHistory.push_back(newMovie); // Add pointer to vector history
        saveHistory(); // Save immediately to secure history file
    }
}

void App::viewHistory() const {
    if (searchHistory.empty()) {
        std::cout << "\nSearch history is empty.\n";
        return;
    }

    while (true) {
        std::cout << "\n=== Search History ===\n";
        for (size_t i = 0; i < searchHistory.size(); ++i) {
            std::cout << i + 1 << ". " << searchHistory[i]->getTitle() 
                      << " (" << searchHistory[i]->getYear() << ")\n";
        }
        std::cout << "\nEnter a number to view full details (or 0 to return): ";
        int indexChoice = 0;
        if (!(std::cin >> indexChoice)) {
            std::cout << "Invalid input. Returning to menu.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            break;
        }
        std::cin.ignore(10000, '\n');

        if (indexChoice == 0) {
            break;
        }

        if (indexChoice > 0 && static_cast<size_t>(indexChoice) <= searchHistory.size()) {
            searchHistory[indexChoice - 1]->display();
        } else {
            std::cout << "Invalid choice. Please select a number between 1 and " << searchHistory.size() << ".\n";
        }
    }
}

void App::clearHistory(bool clearDisk) {
    for (Movie* m : searchHistory) {
        delete m; // Free memory for each movie
    }
    searchHistory.clear(); // Empty the vector

    if (clearDisk) {
        // Truncate the file so history is cleared on disk too
        std::ofstream outFile("history.txt", std::ios::trunc);
    }
}

void App::loadHistory() {
    std::ifstream inFile("history.txt");
    if (!inFile) return;

    std::string title, year, director, plot, rating;
    while (std::getline(inFile, title) &&
           std::getline(inFile, year) &&
           std::getline(inFile, director) &&
           std::getline(inFile, plot) &&
           std::getline(inFile, rating)) {
        if (!title.empty()) {
            searchHistory.push_back(new Movie(title, year, director, plot, rating));
        }
    }
}

void App::saveHistory() const {
    std::ofstream outFile("history.txt", std::ios::trunc);
    if (!outFile) return;

    for (const Movie* m : searchHistory) {
        outFile << m->getTitle() << "\n";
        outFile << m->getYear() << "\n";
        outFile << m->getDirector() << "\n";
        outFile << m->getPlot() << "\n";
        outFile << m->getRating() << "\n";
    }
}
