// =====================================================
// Name: Michael Tran
// Course: ITSE 2359 C++ Programming
// Project: StreamSort++ (Units 14-16 Integration)
// File: main.cpp
// =====================================================

#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <string>
#include "StreamQueue.h"

// -------------------------------------------------------
// printMenu
// Displays the main menu options to the user.
// -------------------------------------------------------
void printMenu() {
    std::cout << "\n=== StreamSort++ Queue Manager ===\n";
    std::cout << "  1. Add show\n";
    std::cout << "  2. Remove show\n";
    std::cout << "  3. Display all shows\n";
    std::cout << "  4. Sort by rating\n";
    std::cout << "  5. Search by title\n";
    std::cout << "  6. Sum of all ratings\n";
    std::cout << "  7. Display highest-rated show\n";
    std::cout << "  8. Exit\n";
    std::cout << "----------------------------------\n";
    std::cout << "Choice: ";
}

int main() {
    StreamQueue queue;
    int choice = 0;

    do {
        printMenu();

        // --- Input validation: ensure the user enters an integer ---
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ERROR: Please enter a valid menu number (1-8).\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {

        // -------------------------------------------------------
        // Option 1 — Add a show
        // -------------------------------------------------------
        case 1: {
            std::string title;
            double rating = 0.0;

            std::cout << "Title: ";
            std::getline(std::cin, title);

            std::cout << "Rating (0-10): ";
            if (!(std::cin >> rating)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "ERROR: Rating must be a number.\n";
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            try {
                queue.addShow(title, rating);
            } catch (const std::invalid_argument&) {
                // User-friendly message — not raw exception text
                std::cout << "ERROR: Rating must be between 0.0 and 10.0.\n";
            }
            break;
        }

        // -------------------------------------------------------
        // Option 2 — Remove a show by index
        // -------------------------------------------------------
        case 2: {
            int index = 0;
            std::cout << "Enter index to remove: ";
            if (!(std::cin >> index)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "ERROR: Index must be an integer.\n";
                break;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            try {
                queue.removeShow(index);
            } catch (const std::out_of_range&) {
                std::cout << "ERROR: That index does not exist in the queue.\n";
            }
            break;
        }

        // -------------------------------------------------------
        // Option 3 — Display all shows
        // -------------------------------------------------------
        case 3:
            std::cout << "\n--- Current Queue ---\n";
            queue.displayAll();
            break;

        // -------------------------------------------------------
        // Option 4 — Sort by rating
        // -------------------------------------------------------
        case 4:
            queue.sortByRating();
            break;

        // -------------------------------------------------------
        // Option 5 — Search by title
        // -------------------------------------------------------
        case 5: {
            std::string query;
            std::cout << "Search title: ";
            std::getline(std::cin, query);
            queue.searchByTitle(query);
            break;
        }

        // -------------------------------------------------------
        // Option 6 — Sum of all ratings (recursive)
        // -------------------------------------------------------
        case 6:
            if (queue.size() == 0) {
                std::cout << "Queue is empty — nothing to sum.\n";
            } else {
                double total = queue.sumRatings(0);
                std::cout << std::fixed << std::setprecision(2);
                std::cout << "Sum of all ratings: " << total
                          << " (via recursion)\n";
            }
            break;

        // -------------------------------------------------------
        // Option 7 — Display highest-rated show (recursive)
        // -------------------------------------------------------
        case 7:
            if (queue.size() == 0) {
                std::cout << "Queue is empty — no top show.\n";
            } else {
                int topIdx = queue.findHighest(0);
                // Re-display by printing the queue and highlighting top
                std::cout << "Highest-rated show found by recursion:\n";
                queue.displayAll();
                std::cout << "  --> Top show is at index [" << topIdx << "]\n";
            }
            break;

        // -------------------------------------------------------
        // Option 8 — Exit
        // -------------------------------------------------------
        case 8:
            std::cout << "Goodbye!\n";
            break;

        // -------------------------------------------------------
        // Invalid menu number
        // -------------------------------------------------------
        default:
            std::cout << "ERROR: Please enter a number between 1 and 8.\n";
            break;
        }

    } while (choice != 8);

    return 0;
}
