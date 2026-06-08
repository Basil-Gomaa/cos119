#include "Movie.h"
#include <iostream>

Movie::Movie(std::string t, std::string y, std::string d, std::string p, std::string r)
    : title(t), year(y), director(d), plot(p), rating(r) {}

std::string Movie::getTitle() const { return title; }
std::string Movie::getYear() const { return year; }
std::string Movie::getDirector() const { return director; }
std::string Movie::getPlot() const { return plot; }
std::string Movie::getRating() const { return rating; }

void Movie::display() const {
    std::cout << "\n=====================================\n";
    std::cout << "Title:    " << title << " (" << year << ")\n";
    std::cout << "Director: " << director << "\n";
    std::cout << "Rating:   " << rating << "\n";
    std::cout << "Plot:     " << plot << "\n";
    std::cout << "=====================================\n";
}
