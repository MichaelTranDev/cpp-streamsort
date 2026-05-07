// =====================================================
// Name: Michael Tran
// Course: ITSE 2359 C++ Programming
// Project: StreamSort++ (Units 14-16 Integration)
// File: StreamQueue.cpp
// =====================================================

#include "StreamQueue.h"
#include <iostream>
#include <algorithm>   // std::transform
#include <iomanip>     // std::fixed, std::setprecision

// -------------------------------------------------------
// addShow
// Appends a title/rating pair to the queue.
// Throws std::invalid_argument if rating is out of [0, 10].
// -------------------------------------------------------
void StreamQueue::addShow(std::string title, double rating) {
    if (rating < 0.0 || rating > 10.0) {
        throw std::invalid_argument("Rating must be between 0.0 and 10.0.");
    }
    titles.push_back(title);
    ratings.push_back(rating);
    std::cout << "Added: " << title << " (" << std::fixed
              << std::setprecision(1) << rating << ")\n";
}

// -------------------------------------------------------
// removeShow
// Removes the title/rating at the given index.
// Throws std::out_of_range if index is invalid.
// -------------------------------------------------------
void StreamQueue::removeShow(int index) {
    if (index < 0 || index >= static_cast<int>(titles.size())) {
        throw std::out_of_range("Index " + std::to_string(index) +
                                " is out of range. Queue has " +
                                std::to_string(titles.size()) + " item(s).");
    }
    std::cout << "Removed: " << titles[index] << "\n";
    titles.erase(titles.begin() + index);
    ratings.erase(ratings.begin() + index);
}

// -------------------------------------------------------
// displayAll
// Prints every show with its index and rating.
// -------------------------------------------------------
void StreamQueue::displayAll() const {
    if (titles.empty()) {
        std::cout << "  (Queue is empty)\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(1);
    for (int i = 0; i < static_cast<int>(titles.size()); ++i) {
        std::cout << "  [" << i << "] " << titles[i]
                  << " — " << ratings[i] << "\n";
    }
}

// -------------------------------------------------------
// sortByRating
// Sorts shows from highest to lowest rating using
// selection sort (no STL sort per project spirit).
// -------------------------------------------------------
void StreamQueue::sortByRating() {
    int n = static_cast<int>(titles.size());
    for (int i = 0; i < n - 1; ++i) {
        int maxIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (ratings[j] > ratings[maxIdx]) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            std::swap(ratings[i], ratings[maxIdx]);
            std::swap(titles[i],  titles[maxIdx]);
        }
    }
    std::cout << "Queue sorted by rating (highest first).\n";
}

// -------------------------------------------------------
// searchByTitle
// Case-insensitive linear search for a show by title.
// -------------------------------------------------------
void StreamQueue::searchByTitle(std::string query) const {
    // Convert query to lowercase for case-insensitive comparison
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);

    bool found = false;
    std::cout << std::fixed << std::setprecision(1);
    for (int i = 0; i < static_cast<int>(titles.size()); ++i) {
        std::string lower = titles[i];
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        if (lower.find(query) != std::string::npos) {
            std::cout << "  Found [" << i << "]: " << titles[i]
                      << " — " << ratings[i] << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "  No shows found matching \"" << query << "\".\n";
    }
}

// -------------------------------------------------------
// RECURSIVE FUNCTION: sumRatings
// Base case:   index >= ratings.size() -- return 0.0
// General case: return ratings[index] + sumRatings(index + 1)
// -------------------------------------------------------
double StreamQueue::sumRatings(int index) const {
    // Base case: past the last element — nothing left to add
    if (index >= static_cast<int>(ratings.size())) {
        return 0.0;
    }
    // General case: current rating plus the sum of everything after it
    return ratings[index] + sumRatings(index + 1);
}

// -------------------------------------------------------
// RECURSIVE FUNCTION: findHighest
// Base case:   index == (int)ratings.size() - 1 -- return index
// General case: compare ratings[index] with findHighest(index + 1),
//               return the index whose rating is greater
// -------------------------------------------------------
int StreamQueue::findHighest(int index) const {
    // Base case: only one element left to consider
    if (index == static_cast<int>(ratings.size()) - 1) {
        return index;
    }
    // General case: find the highest in the rest of the list
    int bestRest = findHighest(index + 1);
    return (ratings[index] >= ratings[bestRest]) ? index : bestRest;
}

// -------------------------------------------------------
// size
// Returns the number of shows currently in the queue.
// -------------------------------------------------------
int StreamQueue::size() const {
    return static_cast<int>(titles.size());
}
