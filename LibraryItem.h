// LibraryItem.h
#ifndef LIBRARY_ITEM_H
#define LIBRARY_ITEM_H

#include <string>

class LibraryItem {
protected:
    int id;             // Unique identifier for the library item
    double cost;        // Cost of the library item
    int loanPeriod;     // Loan period in days for the library item

public:
    // Constructor with parameters to initialize the LibraryItem object
    LibraryItem(int id, double cost, int loanPeriod);

    // Enumeration for different status of the library item
    enum class Status { 
        In,     // Item is in the library
        Out,    // Item is checked out
        Lost    // Item is reported lost
    };
    Status status;  // Current status of the library item
    bool lost;      // Flag indicating if the item is lost

    // Accessor functions to retrieve private member variables
    int getId() const;                 // Getter for id
    double getCost() const;            // Getter for cost
    std::string getStatusString() const; // Getter to convert Status enum to string
    int getLoanPeriod() const;         // Getter for loan period

    // Mutator functions to modify private member variables
    void setId(int id);                // Setter for id
    void setCost(double cost);         // Setter for cost
    void setStatus(Status status);     // Setter for status
    void setLoanPeriod(int loanPeriod);// Setter for loan period
    void reportLost();                 // Method to mark the item as lost

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~LibraryItem() = default;
};

#endif // LIBRARY_ITEM_H
