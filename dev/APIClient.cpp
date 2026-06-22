#include "APIClient.h"
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <sstream>
#include <iomanip>
#include <cctype>

APIClient::APIClient(std::string key) : apiKey(key) {}

std::string APIClient::urlEncode(const std::string& value) const {
    std::ostringstream escaped;
    escaped << std::hex;
    for (char c : value) {
        if (isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else if (c == ' ') {
            escaped << '+';
        } else {
            escaped << '%' << std::setw(2) << std::setfill('0') << std::uppercase << (int)static_cast<unsigned char>(c);
        }
    }
    return escaped.str();
}

std::string APIClient::extractJSONValue(const std::string& json, const std::string& key) const {
    std::string searchKey = "\"" + key + "\"";
    size_t keyPos = json.find(searchKey);
    if (keyPos == std::string::npos) return "N/A";

    size_t colonPos = json.find(":", keyPos + searchKey.length());
    if (colonPos == std::string::npos) return "N/A";

    size_t valStart = colonPos + 1;
    while (valStart < json.length() && (json[valStart] == ' ' || json[valStart] == '\t' || json[valStart] == '\r' || json[valStart] == '\n')) {
        valStart++;
    }

    if (valStart >= json.length()) return "N/A";

    if (json[valStart] == '"') {
        valStart++; // Skip starting quote
        std::string val = "";
        bool escaped = false;
        for (size_t i = valStart; i < json.length(); i++) {
            if (escaped) {
                if (json[i] == '"') {
                    val += '"';
                } else if (json[i] == '\\') {
                    val += '\\';
                } else {
                    val += json[i];
                }
                escaped = false;
            } else if (json[i] == '\\') {
                escaped = true;
            } else if (json[i] == '"') {
                return val; // End quote reached
            } else {
                val += json[i];
            }
        }
        return "N/A";
    } else {
        // Numeric or boolean value
        size_t valEnd = valStart;
        while (valEnd < json.length() && json[valEnd] != ',' && json[valEnd] != '}' && json[valEnd] != ']') {
            valEnd++;
        }
        std::string val = json.substr(valStart, valEnd - valStart);
        while (!val.empty() && (val.back() == ' ' || val.back() == '\t' || val.back() == '\r' || val.back() == '\n')) {
            val.pop_back();
        }
        return val;
    }
}

Movie* APIClient::fetchMovie(std::string title) const {
    std::string encodedTitle = urlEncode(title);
    std::string url = "http://www.omdbapi.com/?t=" + encodedTitle + "&apikey=" + apiKey;
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

    // Basic check if the movie was found or API returned False
    if (result.find("\"Response\":\"False\"") != std::string::npos) {
        std::string errorMsg = extractJSONValue(result, "Error");
        std::cout << "\nAPI Error: " << errorMsg << "\n";
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
