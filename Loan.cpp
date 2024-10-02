//Loan.cpp
#include "Loan.h"
#include <ctime>

// Constructor with parameters
Loan::Loan(int loanId, int bookId, int patronId)
    : loanId(loanId), bookId(bookId), patronId(patronId), currentStatus(Status::Normal) {
    dueDate = time(nullptr) + 24 * 60 * 60 * 10; // Set due date 10 days from now
}

// Getter methods
int Loan::getLoanId() const { return loanId; }               // Return the loan ID
int Loan::getBookId() const { return bookId; }               // Return the book ID
int Loan::getPatronId() const { return patronId; }           // Return the patron ID
time_t Loan::getDueDate() const { return dueDate; }          // Return the due date
Loan::Status Loan::getCurrentStatus() const { return currentStatus; }  // Return the current status

// Setter methods
void Loan::setLoanId(int loanId) { this->loanId = loanId; }      // Set the loan ID
void Loan::setBookId(int bookId) { this->bookId = bookId; }      // Set the book ID
void Loan::setPatronId(int patronId) { this->patronId = patronId; }  // Set the patron ID
void Loan::setDueDate(time_t dueDate) { this->dueDate = dueDate; }  // Set the due date
void Loan::setCurrentStatus(Status status) { this->currentStatus = status; }  // Set the current status

// Method to update the status of the loan (Normal or Overdue)
void Loan::updateStatus() {
    if (time(nullptr) > dueDate) {          // Check if current time has exceeded due date
        currentStatus = Status::Overdue;    // Update status to Overdue if true
    }
}

// Method to check if the loan is overdue
bool Loan::isOverdue() const {
    return time(nullptr) > dueDate;         // Return true if current time has exceeded due date
}

// Method to recheck the loan status and extend due date by 10 days
void Loan::recheck() {
    dueDate = time(nullptr) + 24 * 60 * 60 * 10;   // Extend due date by 10 days from now
    currentStatus = Status::Normal;                // Reset status to Normal
}

// Method to get a string representation of the loan status
string Loan::getStatusString() const {
    return (currentStatus == Status::Normal) ? "Normal" : "Overdue";  // Return "Normal" or "Overdue" based on current status
}
