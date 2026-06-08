#include "APIClient.h"
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

APIClient::APIClient(std::string key) : apiKey(key) {}

std::string APIClient::extractJSONValue(const std::string& json, const std::string& key) const {
    std::string searchKey = "\"" + key + "\":\"";
    size_t startPos = json.find(searchKey);
    if (startPos == std::string::npos) return "N/A";
    
    startPos += searchKey.length();
    size_t endPos = json.find("\"", startPos);
    if (endPos == std::string::npos) return "N/A";
    
    return json.substr(startPos, endPos - startPos);
}

Movie* APIClient::fetchMovie(std::string title) const {
    // Replace spaces with '+' for the URL
    for (size_t i = 0; i < title.length(); i++) {
        if (title[i] == ' ') title[i] = '+';
    }

    std::string url = "http://www.omdbapi.com/?t=" + title + "&apikey=" + apiKey;
    std::string command = "curl.exe -s \"" + url + "\"";
    
    std::string result;
    char buffer[128];
    
    // Using _popen for Windows to execute curl
#ifdef _WIN32
    FILE* pipe = _popen(command.c_str(), "r");
#else
    FILE* pipe = popen(command.c_str(), "r");
#endif

    if (!pipe) {
        std::cerr << "Error: Could not execute curl command.\n";
        return nullptr;
    }
    
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    
#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif

    // Basic check if the movie was found
    if (result.find("\"Response\":\"False\"") != std::string::npos) {
        return nullptr;
    }

    // Extract fields manually
    std::string mTitle = extractJSONValue(result, "Title");
    std::string mYear = extractJSONValue(result, "Year");
    std::string mDirector = extractJSONValue(result, "Director");
    std::string mPlot = extractJSONValue(result, "Plot");
    std::string mRating = extractJSONValue(result, "imdbRating");

    // Dynamically allocate a new Movie object
    return new Movie(mTitle, mYear, mDirector, mPlot, mRating);
}
