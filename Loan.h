//Loan.h
#ifndef LOAN_H
#define LOAN_H

#include <string>
#include <ctime>

using namespace std;

class Loan {
private:
    int loanId;         // Unique ID for the loan
    int bookId;         // ID of the book borrowed
    int patronId;       // ID of the patron borrowing the book
    time_t dueDate;     // Due date of the loan

public:
    // Constructor with parameters for initializing loan details
    Loan(int loanId, int bookId, int patronId);

    // Enumeration for the status of the loan
    enum class Status { Normal, Overdue };
    Status currentStatus;   // Current status of the loan

    // Accessor methods for retrieving loan information
    int getLoanId() const;          // Return the loan ID
    int getBookId() const;          // Return the book ID
    int getPatronId() const;        // Return the patron ID
    time_t getDueDate() const;      // Return the due date
    Status getCurrentStatus() const;// Return the current status of the loan

    // Mutator methods for modifying loan attributes
    void setLoanId(int loanId);         // Set the loan ID
    void setBookId(int bookId);         // Set the book ID
    void setPatronId(int patronId);     // Set the patron ID
    void setDueDate(time_t dueDate);    // Set the due date
    void setCurrentStatus(Status status);   // Set the current status of the loan

    // Method to update the status of the loan (Normal or Overdue)
    void updateStatus();

    // Method to check if the loan is overdue
    bool isOverdue() const;

    // Method to recheck the loan status and extend due date by 10 days
    void recheck();

    // Method to get a string representation of the loan status
    string getStatusString() const;
};

#endif // LOAN_H
