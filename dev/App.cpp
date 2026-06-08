#include "App.h"
#include <iostream>
#include <string>

App::App(std::string apiKey) : apiClient(apiKey) {}

App::~App() {
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
        
        std::cin >> choice;
        std::cin.ignore(); // Clear newline from buffer

        switch (choice) {
            case 1:
                searchMovie();
                break;
            case 2:
                viewHistory();
                break;
            case 3:
                clearHistory();
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

    std::cout << "Fetching data...\n";
    Movie* newMovie = apiClient.fetchMovie(title);

    if (newMovie != nullptr) {
        newMovie->display();
        searchHistory.push_back(newMovie); // Add pointer to vector history
    } else {
        std::cout << "Movie not found or error occurred.\n";
    }
}

void App::viewHistory() const {
    if (searchHistory.empty()) {
        std::cout << "\nSearch history is empty.\n";
        return;
    }

    std::cout << "\n=== Search History ===\n";
    for (size_t i = 0; i < searchHistory.size(); ++i) {
        std::cout << i + 1 << ". " << searchHistory[i]->getTitle() 
                  << " (" << searchHistory[i]->getYear() << ")\n";
    }
}

void App::clearHistory() {
    for (Movie* m : searchHistory) {
        delete m; // Free memory for each movie
    }
    searchHistory.clear(); // Empty the vector
}
