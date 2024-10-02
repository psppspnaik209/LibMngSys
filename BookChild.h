// BookChild.h
#ifndef BOOK_CHILD_H
#define BOOK_CHILD_H

#include "LibraryItem.h" // Include base class header file
#include <string>

class BookChild : public LibraryItem {
private:
    std::string author;      // Author of the book
    std::string title;       // Title of the book
    std::string isbnNumber;  // ISBN number of the book

public:
    // Category enumeration for different book categories
    enum class Category { 
        Biography,  // Biography category
        Fiction,    // Fiction category
        SciFi,      // Science Fiction category
        History     // History category
    };
    Category category; // Category of the book

    // Constructor with parameters to initialize the BookChild object
    BookChild(int id, double cost, int loanPeriod, std::string author, std::string title,
              std::string isbnNumber, Category category);

    // Accessor functions to retrieve private member variables
    std::string getAuthor() const;      // Getter for author
    std::string getTitle() const;       // Getter for title
    std::string getIsbnNumber() const;  // Getter for ISBN number
    std::string getCategoryString() const; // Getter to convert Category enum to string

    // Mutator functions to modify private member variables
    void setAuthor(const std::string& author);       // Setter for author
    void setTitle(const std::string& title);         // Setter for title
    void setIsbnNumber(const std::string& isbnNumber); // Setter for ISBN number
    void setCategory(Category category);             // Setter for category
};

#endif // BOOK_CHILD_H
