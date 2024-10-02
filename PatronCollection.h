#ifndef PATRON_COLLECTION_H
#define PATRON_COLLECTION_H

#include <vector>
#include "Patron.h"

class PatronCollection {
private:
    std::vector<Patron> patrons;        // Collection of patrons

public:
    // Add a new patron to the collection
    void addPatron(const Patron& patron);

    // Update an existing patron's details
    void editPatron(int idNumber, const Patron& updatedPatron);

    // Delete a patron from the collection by their ID number
    void deletePatron(int idNumber);

    // Find and return a pointer to a patron based on their ID number
    Patron* findPatron(int idNumber);

    // Print details of all patrons in the collection
    void printAllPatrons() const;

    // Print details of a specific patron based on their ID number
    void printPatronDetails(int idNumber) const;

    // Get a const reference to the vector containing all patrons
    const std::vector<Patron>& getAllPatrons() const { return patrons; }
};

// Overloaded insertion operator for Patron, allows printing patron details
std::ostream& operator<<(std::ostream& os, const Patron& patron);

#endif // PATRON_COLLECTION_H