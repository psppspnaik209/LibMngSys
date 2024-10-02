// LibraryItemCollection.h
#ifndef LIBRARY_ITEM_COLLECTION_H
#define LIBRARY_ITEM_COLLECTION_H

#include <vector>
#include <memory>
#include "LibraryItem.h"

class LibraryItemCollection {
private:
    std::vector<std::unique_ptr<LibraryItem>> items; // Vector of unique pointers to LibraryItem objects

public:
    // Function to add a new item to the collection
    void addItem(std::unique_ptr<LibraryItem> item);

    // Function to edit an existing item in the collection
    void editItem(int id, const LibraryItem& updatedItem);

    // Function to delete an item from the collection by id
    void deleteItem(int id);

    // Function to find an item in the collection by id
    LibraryItem* findItem(int id);

    // Function to print details of all items in the collection
    void printAllItems() const;

    // Function to print details of an item in the collection by id
    void printItemDetails(int id) const;

    // Function to report an item as lost by itemId
    void reportLost(int itemId);

    // Function to get a const reference to the vector of all items in the collection
    const std::vector<std::unique_ptr<LibraryItem>>& getAllItems() const;
};

// Overloaded insertion operator to print item details
std::ostream& operator<<(std::ostream& os, const LibraryItem& item);

#endif // LIBRARY_ITEM_COLLECTION_H
