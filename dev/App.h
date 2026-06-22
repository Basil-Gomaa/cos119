#ifndef APP_H
#define APP_H

#include <vector>
#include "APIClient.h"
#include "Movie.h"

class App {
private:
    std::vector<Movie*> searchHistory; // 1D vector of pointers
    APIClient apiClient;

    void searchMovie();
    void viewHistory() const;
    void clearHistory(bool clearDisk = false);

    // Persistency helper methods
    void loadHistory();
    void saveHistory() const;

public:
    App(std::string apiKey);
    ~App(); // Destructor to clean up dynamic memory

    void run(); // Main application loop
};

#endif // APP_H
