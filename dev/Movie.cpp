#include "Movie.h"
#include <iostream>

Movie::Movie(std::string t, std::string y, std::string d, std::string p, std::string r)
    : title(t), year(y), director(d), plot(p), rating(r) {}

std::string Movie::getTitle() const { return title; }
std::string Movie::getYear() const { return year; }
std::string Movie::getDirector() const { return director; }
std::string Movie::getPlot() const { return plot; }
std::string Movie::getRating() const { return rating; }

void Movie::printWrappedField(const std::string& label, const std::string& text, size_t boxWidth) const {
    size_t labelWidth = label.length();
    size_t textWidthLimit = boxWidth - labelWidth - 4; // 4 accounts for "| " and " |"

    if (textWidthLimit <= 0) return;

    std::string indent(labelWidth, ' ');
    size_t i = 0;
    bool firstLine = true;

    while (i < text.length()) {
        if (!firstLine) {
            while (i < text.length() && text[i] == ' ') {
                i++;
            }
        }
        if (i >= text.length()) break;

        size_t chunkLength = textWidthLimit;
        if (i + chunkLength < text.length()) {
            size_t lastSpace = text.find_last_of(' ', i + chunkLength);
            if (lastSpace != std::string::npos && lastSpace > i) {
                chunkLength = lastSpace - i;
            }
        } else {
            chunkLength = text.length() - i;
        }

        std::string chunk = text.substr(i, chunkLength);

        if (firstLine) {
            std::cout << "| " << label << chunk;
            size_t printed = labelWidth + chunk.length();
            std::cout << std::string(boxWidth - printed - 4, ' ') << " |\n";
            firstLine = false;
        } else {
            std::cout << "| " << indent << chunk;
            size_t printed = labelWidth + chunk.length();
            std::cout << std::string(boxWidth - printed - 4, ' ') << " |\n";
        }

        i += chunkLength;
        if (i < text.length() && text[i] == ' ') {
            i++;
        }
    }

    if (firstLine) {
        std::cout << "| " << label;
        std::cout << std::string(boxWidth - labelWidth - 4, ' ') << " |\n";
    }
}

void Movie::display() const {
    size_t boxWidth = 70;
    std::string border(boxWidth - 2, '-');

    std::cout << "\n+" << border << "+\n";
    printWrappedField("Title:    ", title + " (" + year + ")", boxWidth);
    printWrappedField("Director: ", director, boxWidth);
    printWrappedField("Rating:   ", rating, boxWidth);
    printWrappedField("Plot:     ", plot, boxWidth);
    std::cout << "+" << border << "+\n";
}
