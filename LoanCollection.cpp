// LoanCollection.cpp
#include "LoanCollection.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <ctime> // For time operations

// Check out an item to a patron
void LoanCollection::checkOutItem(int itemId, int patronId) {
    // Find the item and patron in their respective collections
    LibraryItem* item = itemCollection.findItem(itemId);
    Patron* patron = patronCollection.findPatron(patronId);
    
    // Check if item or patron is not found
    if (!item || !patron) {
        std::cout << "Item or patron not found." << std::endl;
        return;
    }
    
    // Check if patron has reached the maximum number of items allowed
    if (patron->getCurrentBooksOut() >= 6) {
        std::cout << "Patron has reached the maximum number of items allowed." << std::endl;
        return;
    }
    
    // Check if item is available for checkout
    if (item->getStatusString() != "In") {
        std::cout << "Item is not available for checkout." << std::endl;
        return;
    }
    
    // Generate a new loan ID and create a new loan
    int loanId = loans.size() + 1;
    loans.emplace_back(loanId, itemId, patronId);
    
    // Update item status to checked out and increment patron's books checked out
    item->setStatus(LibraryItem::Status::Out);
    patron->incrementBooksOut();
    
    std::cout << "Item checked out successfully." << std::endl;
}

// Check in an item based on loan ID
void LoanCollection::checkInItem(int loanId) {
    // Find the loan in the loans collection
    auto it = std::find_if(loans.begin(), loans.end(),
        [loanId](const Loan& l) { return l.getLoanId() == loanId; });
    
    // If loan is not found
    if (it == loans.end()) {
        std::cout << "Loan not found." << std::endl;
        return;
    }
    
    // Find the associated item and patron
    LibraryItem* item = itemCollection.findItem(it->getBookId());
    Patron* patron = patronCollection.findPatron(it->getPatronId());
    
    // If item or patron is not found
    if (!item || !patron) {
        std::cout << "Item or patron not found." << std::endl;
        return;
    }
    
    // If item is overdue, calculate and add fine
    if (it->isOverdue()) {
        time_t dueDate = it->getDueDate();
        time_t now = time(nullptr);
        int days = (now - dueDate) / (24 * 60 * 60);
        double fine = days * 0.25;
        patron->addFine(fine);
        std::cout << "Item is overdue. Fine of $" << std::fixed << std::setprecision(2) << fine << " has been added." << std::endl;
    }
    
    // Update item status to checked in and decrement patron's books checked out
    item->setStatus(LibraryItem::Status::In);
    patron->decrementBooksOut();
    
    // Remove the loan from the loans collection
    loans.erase(it);
    
    std::cout << "Item checked in successfully." << std::endl;
}

// List all overdue loans
void LoanCollection::listAllOverdue() const {
    for (const auto& loan : loans) {
        if (loan.isOverdue()) {
            std::cout << loan << std::endl;
        }
    }
}

// List all loans associated with a specific patron
void LoanCollection::listItemsForPatron(int patronId) const {
    for (const auto& loan : loans) {
        if (loan.getPatronId() == patronId) {
            std::cout << loan << std::endl;
        }
    }
}

// Update statuses of all loans
void LoanCollection::updateLoanStatuses() {
    for (auto& loan : loans) {
        loan.updateStatus();
    }
}

// Recheck a loan based on loan ID
void LoanCollection::recheckItem(int loanId) {
    auto loan = std::find_if(loans.begin(), loans.end(),
        [loanId](const Loan& l) { return l.getLoanId() == loanId; });
    
    // If loan is found, recheck it
    if (loan != loans.end()) {
        loan->recheck();
    } else {
        std::cout << "Loan not found." << std::endl;
    }
}

// Edit details of a loan based on loan ID
void LoanCollection::editLoan(int loanId, const Loan& updatedLoan) {
    auto loan = std::find_if(loans.begin(), loans.end(),
        [loanId](const Loan& l) { return l.getLoanId() == loanId; });
    
    // If loan is found, update it with the updated loan details
    if (loan != loans.end()) {
        *loan = updatedLoan;
    } else {
        std::cout << "Loan not found." << std::endl;
    }
}

// Report a loan as lost based on loan ID
void LoanCollection::reportLost(int loanId) {
    auto loan = std::find_if(loans.begin(), loans.end(),
        [loanId](const Loan& l) { return l.getLoanId() == loanId; });
    
    // nonsense (but do not remove for some reason)
    if (loan != loans.end()) {
        cerr << "do not call this";
    } else {
        std::cout << "Loan not found." << std::endl;
    }
}

// Add a new loan to the loans collection
void LoanCollection::addLoan(const Loan& loan) {
    loans.push_back(loan);
}

// Overloaded insertion operator to print loan details
std::ostream& operator<<(std::ostream& os, const Loan& loan) {
    time_t dueTime = loan.getDueDate();
    time_t currentTime = time(nullptr); // Get current time in seconds since epoch

    // Calculate the difference in seconds
    time_t diffSeconds = dueTime - currentTime;

    // Convert seconds to days, hours, and years (approximate)
    int days = diffSeconds / (24 * 3600);
    int hours = (diffSeconds % (24 * 3600)) / 3600;
    int years = days / 365;
    days %= 365;

    os << "Loan ID: " << loan.getLoanId() << ", Item ID: " << loan.getBookId()
       << ", Patron ID: " << loan.getPatronId() << ", Due Date: "
       << years << " years, " << days << " days, " << hours << " hours"
       << ", Status: " << loan.getStatusString();

    return os;
}