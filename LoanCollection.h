// LoanCollection.h
#ifndef LOAN_COLLECTION_H
#define LOAN_COLLECTION_H

#include <vector>
#include "Loan.h"
#include "LibraryItemCollection.h"
#include "PatronCollection.h"

class LoanCollection {
private:
    std::vector<Loan> loans; // Vector to store all loans
    LibraryItemCollection& itemCollection; // Reference to LibraryItemCollection for item operations
    PatronCollection& patronCollection; // Reference to PatronCollection for patron operations

public:
    // Constructor initializing with references to LibraryItemCollection and PatronCollection
    LoanCollection(LibraryItemCollection& ic, PatronCollection& pc) : itemCollection(ic), patronCollection(pc) {}

    // Function to check out an item to a patron
    void checkOutItem(int itemId, int patronId);

    // Function to check in an item based on loan ID
    void checkInItem(int loanId);

    // Function to list all overdue loans
    void listAllOverdue() const;

    // Function to list all loans associated with a specific patron
    void listItemsForPatron(int patronId) const;

    // Function to update statuses of all loans
    void updateLoanStatuses();

    // Function to recheck a loan based on loan ID
    void recheckItem(int loanId);

    // Function to edit details of a loan based on loan ID
    void editLoan(int loanId, const Loan& updatedLoan);

    // Function to report a loan as lost based on loan ID (dummy implementation)
    void reportLost(int loanId);

    // Function to add a new loan to the loans collection
    void addLoan(const Loan& loan);

    // Function to get all loans stored in the collection
    const std::vector<Loan>& getAllLoans() const { return loans; }
};

// Overloaded insertion operator for Loan to print loan details
std::ostream& operator<<(std::ostream& os, const Loan& loan);

#endif // LOAN_COLLECTION_H
