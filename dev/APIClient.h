#ifndef APICLIENT_H
#define APICLIENT_H

#include <string>
#include "Movie.h"

class APIClient {
private:
    std::string apiKey;

    // Helper to extract a JSON value from a raw string manually
    std::string extractJSONValue(const std::string& json, const std::string& key) const;

public:
    APIClient(std::string key);

    // Fetches movie data and returns a dynamically allocated Movie pointer, 
    // or nullptr if not found.
    Movie* fetchMovie(std::string title) const;
};

#endif // APICLIENT_H
