// LibraryItem.cpp
#include "LibraryItem.h"

// Constructor initializing LibraryItem with parameters
LibraryItem::LibraryItem(int id, double cost, int loanPeriod)
    : id(id), cost(cost), status(Status::In), loanPeriod(loanPeriod) {}

// Getter functions to retrieve private member variables
int LibraryItem::getId() const { return id; }
double LibraryItem::getCost() const { return cost; }

// Converts Status enum to string representation
std::string LibraryItem::getStatusString() const {
    switch (status) {
        case Status::In: return "In";     // Return "In" for In status
        case Status::Out: return "Out";   // Return "Out" for Out status
        case Status::Lost: return "Lost"; // Return "Lost" for Lost status
        default: return "Unknown";        // Default case if status is unknown
    }
}

int LibraryItem::getLoanPeriod() const { return loanPeriod; }

// Setter functions to modify private member variables
void LibraryItem::setId(int id) { this->id = id; }
void LibraryItem::setCost(double cost) { this->cost = cost; }
void LibraryItem::setStatus(Status status) { this->status = status; }
void LibraryItem::setLoanPeriod(int loanPeriod) { this->loanPeriod = loanPeriod; }

// Method to mark the item as lost
void LibraryItem::reportLost() {
    lost = true;          // Mark the item as lost
    setStatus(Status::Lost); // Set status to Lost
}
