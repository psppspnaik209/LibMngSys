#include "Patron.h"

// Constructor: initializes a Patron object with name, idNumber, and default values for fineBalance and currentBooksOut
Patron::Patron(string name, int idNumber)
    : name(name), idNumber(idNumber), fineBalance(0), currentBooksOut(0) {}

// Getter methods
string Patron::getName() const { return name; }                // Return the name of the patron
int Patron::getIdNumber() const { return idNumber; }           // Return the ID number of the patron
double Patron::getFineBalance() const { return fineBalance; }  // Return the current fine balance
int Patron::getCurrentBooksOut() const { return currentBooksOut; }  // Return the number of books currently checked out

// Setter methods
void Patron::setName(string name) { this->name = name; }       // Set the name of the patron
void Patron::setIdNumber(int idNumber) { this->idNumber = idNumber; }  // Set the ID number of the patron
void Patron::setFineBalance(double fineBalance) { this->fineBalance = fineBalance; }  // Set the fine balance
void Patron::setCurrentBooksOut(int currentBooksOut) { this->currentBooksOut = currentBooksOut; }  // Set the number of books checked out

// Method to add a fine amount to the patron's balance
void Patron::addFine(double amount) { fineBalance += amount; }

// Method to pay off a part or all of the fine balance
void Patron::payFine(double amount) {
    if (amount > fineBalance) {
        fineBalance = 0;  // If amount exceeds the fine balance, set the balance to zero
    } else {
        fineBalance -= amount;  // Otherwise, deduct the amount from the fine balance
    }
}

// Method to increment the count of books currently checked out by the patron
void Patron::incrementBooksOut() { currentBooksOut++; }

// Method to decrement the count of books currently checked out by the patron (if possible)
void Patron::decrementBooksOut() {
    if (currentBooksOut > 0) {
        currentBooksOut--;  // Reduce the count only if books are currently checked out
    }
}
