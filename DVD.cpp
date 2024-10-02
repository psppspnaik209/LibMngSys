// DVD.cpp
#include "DVD.h"

// Constructor initializing DVD with parameters and passing id, cost, loanPeriod to base class
DVD::DVD(int id, double cost, int loanPeriod, std::string title, Category category,
         int runTime, std::string studio, std::string releaseDate)
    : LibraryItem(id, cost, loanPeriod), // Initialize base class LibraryItem
      title(title),                     // Initialize member variables
      category(category),
      runTime(runTime),
      studio(studio),
      releaseDate(releaseDate) {}

// Getter functions to retrieve private member variables
std::string DVD::getTitle() const { return title; }
std::string DVD::getCategoryString() const {
    switch (category) {
        case Category::Action: return "Action";  // Return string representation for Action category
        case Category::SciFi: return "SciFi";    // Return string representation for SciFi category
        case Category::Drama: return "Drama";    // Return string representation for Drama category
        default: return "Unknown";               // Default case if category is unknown
    }
}
int DVD::getRunTime() const { return runTime; }
std::string DVD::getStudio() const { return studio; }
std::string DVD::getReleaseDate() const { return releaseDate; }

// Setter functions to modify private member variables
void DVD::setTitle(const std::string& title) { this->title = title; }
void DVD::setCategory(Category category) { this->category = category; }
void DVD::setRunTime(int runTime) { this->runTime = runTime; }
void DVD::setStudio(const std::string& studio) { this->studio = studio; }
void DVD::setReleaseDate(const std::string& releaseDate) { this->releaseDate = releaseDate; }
