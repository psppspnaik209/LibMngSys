#ifndef PATRON_H
#define PATRON_H

#include <string>

using namespace std;

class Patron {
private:
    string name;          // Name of the patron
    int idNumber;         // ID number of the patron
    double fineBalance;   // Current fine balance of the patron
    int currentBooksOut;  // Number of books currently checked out by the patron

public:
    // Constructor with parameters
    Patron(string name, int idNumber);

    // Accessors (Getter methods)
    string getName() const;            // Return the name of the patron
    int getIdNumber() const;           // Return the ID number of the patron
    double getFineBalance() const;     // Return the current fine balance of the patron
    int getCurrentBooksOut() const;    // Return the number of books currently checked out by the patron

    // Mutators (Setter methods)
    void setName(string name);             // Set the name of the patron
    void setIdNumber(int idNumber);        // Set the ID number of the patron
    void setFineBalance(double fineBalance);  // Set the current fine balance of the patron
    void setCurrentBooksOut(int currentBooksOut);  // Set the number of books currently checked out by the patron

    // Methods to manage fines and books checked out
    void addFine(double amount);        // Add a fine amount to the patron's balance
    void payFine(double amount);        // Pay off part or all of the fine balance
    void incrementBooksOut();           // Increment the count of books currently checked out
    void decrementBooksOut();           // Decrement the count of books currently checked out

};

#endif // PATRON_H
