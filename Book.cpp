//Book.cpp
#include "Book.h"  // Include the header file defining the Book class

// Constructor definition
Book::Book(string author, string title, string isbnNumber, int libraryIdNumber, double cost)
    : author(author), title(title), isbnNumber(isbnNumber), libraryIdNumber(libraryIdNumber), cost(cost), currentStatus(Status::In) {}
    // Initialize member variables with provided values and set currentStatus to Status::In

// Getter methods
string Book::getAuthor() const { return author; }  // Return the author of the book
string Book::getTitle() const { return title; }    // Return the title of the book
string Book::getIsbnNumber() const { return isbnNumber; }  // Return the ISBN number of the book
int Book::getLibraryIdNumber() const { return libraryIdNumber; }  // Return the library ID number of the book
double Book::getCost() const { return cost; }  // Return the cost of the book
Book::Status Book::getCurrentStatus() const { return currentStatus; }  // Return the current status of the book

// Setter methods
void Book::setAuthor(string author) { this->author = author; }  // Set the author of the book
void Book::setTitle(string title) { this->title = title; }      // Set the title of the book
void Book::setIsbnNumber(string isbnNumber) { this->isbnNumber = isbnNumber; }  // Set the ISBN number of the book
void Book::setLibraryIdNumber(int libraryIdNumber) { this->libraryIdNumber = libraryIdNumber; }  // Set the library ID number of the book
void Book::setCost(double cost) { this->cost = cost; }  // Set the cost of the book
void Book::setCurrentStatus(Status status) { this->currentStatus = status; }  // Set the current status of the book

// Method to get string representation of current status
string Book::getStatusString() const {
    switch (currentStatus) {
        case Status::In: return "In";         // Return "In" if the book is available
        case Status::Out: return "Out";       // Return "Out" if the book is borrowed
        case Status::Repair: return "Repair"; // Return "Repair" if the book is under repair
        case Status::Lost: return "Lost";     // Return "Lost" if the book is lost
        default: return "Unknown";            // Return "Unknown" for any other status (though this case might not be reachable)
    }
}
