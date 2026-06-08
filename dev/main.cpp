#include "App.h"

int main() {
    // API key for OMDb (from user)
    std::string apiKey = "e93144a2";

    // Initialize and run the application
    App myMovieApp(apiKey);
    myMovieApp.run();

    return 0;
}
