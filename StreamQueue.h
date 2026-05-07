// =====================================================
// Name: Michael Tran
// Course: ITSE 2359 C++ Programming
// Project: StreamSort++ (Units 14-16 Integration)
// File: StreamQueue.h
// =====================================================

#ifndef STREAMQUEUE_H
#define STREAMQUEUE_H

#include <string>
#include <vector>
#include <stdexcept>

class StreamQueue {
private:
    std::vector<std::string> titles;   // Stores show titles
    std::vector<double>      ratings;  // Stores corresponding ratings (0.0–10.0)

public:
    // --- Core queue operations ---
    void addShow(std::string title, double rating);  // throws invalid_argument
    void removeShow(int index);                       // throws out_of_range
    void displayAll() const;
    void sortByRating();
    void searchByTitle(std::string query) const;

    // --- Recursive functions ---
    // RECURSIVE FUNCTION: sumRatings
    // Base case: index >= ratings.size() -- return 0.0
    // General case: return ratings[index] + sumRatings(index + 1)
    double sumRatings(int index) const;

    // RECURSIVE FUNCTION: findHighest
    // Base case: index == (int)ratings.size() - 1 -- return index
    // General case: compare ratings[index] with findHighest(index + 1), return whichever is higher
    int findHighest(int index) const;

    // --- Utility ---
    int size() const;
};

#endif // STREAMQUEUE_H
