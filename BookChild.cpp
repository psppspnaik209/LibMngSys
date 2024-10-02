// BookChild.cpp
#include "BookChild.h"

// Constructor initializing BookChild with parameters and passing id, cost, loanPeriod to base class
BookChild::BookChild(int id, double cost, int loanPeriod, std::string author, std::string title,
                     std::string isbnNumber, Category category)
    : LibraryItem(id, cost, loanPeriod), // Initialize base class LibraryItem
      author(author),                   // Initialize member variables
      title(title),
      isbnNumber(isbnNumber),
      category(category) {}

// Getter functions to retrieve private member variables
std::string BookChild::getAuthor() const { return author; }
std::string BookChild::getTitle() const { return title; }
std::string BookChild::getIsbnNumber() const { return isbnNumber; }

// Converts Category enum to string representation
std::string BookChild::getCategoryString() const {
    switch (category) {
        case Category::Biography: return "Biography";
        case Category::Fiction: return "Fiction";
        case Category::SciFi: return "SciFi";
        case Category::History: return "History";
        default: return "Unknown";
    }
}

// Setter functions to modify private member variables
void BookChild::setAuthor(const std::string& author) { this->author = author; }
void BookChild::setTitle(const std::string& title) { this->title = title; }
void BookChild::setIsbnNumber(const std::string& isbnNumber) { this->isbnNumber = isbnNumber; }
void BookChild::setCategory(Category category) { this->category = category; }
