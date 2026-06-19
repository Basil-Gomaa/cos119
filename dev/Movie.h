#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie {
private:
    std::string title;
    std::string year;
    std::string director;
    std::string plot;
    std::string rating;

    // Helper to print wrapped fields in the display box
    void printWrappedField(const std::string& label, const std::string& text, size_t boxWidth) const;

public:
    Movie(std::string t, std::string y, std::string d, std::string p, std::string r);

    // Getters
    std::string getTitle() const;
    std::string getYear() const;
    std::string getDirector() const;
    std::string getPlot() const;
    std::string getRating() const;

    // Display movie info
    void display() const;
};

#endif // MOVIE_H
