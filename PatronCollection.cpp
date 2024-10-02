// PatronCollection.cpp
#include "PatronCollection.h"
#include <iostream>
#include <algorithm>

void PatronCollection::addPatron(const Patron& patron) {
    patrons.push_back(patron); // Add a new patron to the collection
}

void PatronCollection::editPatron(int idNumber, const Patron& updatedPatron) {
    // Find the patron with the specified ID number
    auto it = std::find_if(patrons.begin(), patrons.end(),
        [idNumber](const Patron& p) { return p.getIdNumber() == idNumber; });
    
    // If patron is found, update their details with updatedPatron
    if (it != patrons.end()) {
        *it = updatedPatron;
    }
}

void PatronCollection::deletePatron(int idNumber) {
    // Remove the patron with the specified ID number from the collection
    patrons.erase(std::remove_if(patrons.begin(), patrons.end(),
        [idNumber](const Patron& p) { return p.getIdNumber() == idNumber; }),
        patrons.end());
}

Patron* PatronCollection::findPatron(int idNumber) {
    // Find and return a pointer to the patron with the specified ID number
    auto it = std::find_if(patrons.begin(), patrons.end(),
        [idNumber](const Patron& p) { return p.getIdNumber() == idNumber; });
    
    return (it != patrons.end()) ? &(*it) : nullptr;
}

void PatronCollection::printAllPatrons() const {
    // Print details of all patrons in the collection
    for (const auto& patron : patrons) {
        std::cout << patron << std::endl;
    }
}

void PatronCollection::printPatronDetails(int idNumber) const {
    // Find the patron with the specified ID number
    auto it = std::find_if(patrons.begin(), patrons.end(),
        [idNumber](const Patron& p) { return p.getIdNumber() == idNumber; });
    
    // If patron is found, print their details; otherwise, print not found message
    if (it != patrons.end()) {
        std::cout << *it << std::endl;
    } else {
        std::cout << "Patron not found." << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Patron& patron) {
    // Overloaded operator to print patron details
    os << "ID: " << patron.getIdNumber() << ", Name: " << patron.getName()
       << ", Books Out: " << patron.getCurrentBooksOut()
       << ", Fine Balance: $" << patron.getFineBalance();
    return os;
}
