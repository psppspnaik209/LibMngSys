// Book.h
#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
private:
    string author;          // Author of the book
    string title;           // Title of the book
    string isbnNumber;      // ISBN number of the book
    int libraryIdNumber;    // Library ID number of the book
    double cost;            // Cost of the book

public:
    // Constructor with parameters for initializing all member variables
    Book(string author, string title, string isbnNumber, int libraryIdNumber, double cost);

    // Enumeration for the status of the book
    enum class Status { In, Out, Repair, Lost };
    Status currentStatus;   // Current status of the book (currenly only In and Out will be used cuz how can a book be repaired?)

    // Accessor methods for retrieving information about the book
    string getAuthor() const;           // Return the author of the book
    string getTitle() const;            // Return the title of the book
    string getIsbnNumber() const;       // Return the ISBN number of the book
    int getLibraryIdNumber() const;     // Return the library ID number of the book
    double getCost() const;             // Return the cost of the book
    Status getCurrentStatus() const;    // Return the current status of the book

    // Mutator methods for modifying the attributes of the book
    void setAuthor(string author);          // Set the author of the book
    void setTitle(string title);            // Set the title of the book
    void setIsbnNumber(string isbnNumber);  // Set the ISBN number of the book
    void setLibraryIdNumber(int libraryIdNumber);  // Set the library ID number of the book
    void setCost(double cost);              // Set the cost of the book
    void setCurrentStatus(Status status);   // Set the current status of the book

    // Method to obtain a string representation of the current status
    string getStatusString() const;
};

#endif // BOOK_H
