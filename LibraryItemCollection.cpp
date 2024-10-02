// LibraryItemCollection.cpp
#include "LibraryItemCollection.h"
#include "BookChild.h"
#include "AudioCD.h"
#include "DVD.h"
#include <iostream>
#include <algorithm>

// Add a new item to the collection
void LibraryItemCollection::addItem(std::unique_ptr<LibraryItem> item) {
    items.push_back(std::move(item));
}

// Edit an existing item in the collection
void LibraryItemCollection::editItem(int id, const LibraryItem& updatedItem) {
    // Find the item with the specified id
    auto it = std::find_if(items.begin(), items.end(),
        [id](const std::unique_ptr<LibraryItem>& item) { return item->getId() == id; });
    
    // If item found, update it with the provided updatedItem
    if (it != items.end()) {
        **it = updatedItem;
    }
}

// Delete an item from the collection by id
void LibraryItemCollection::deleteItem(int id) {
    // Erase the item with the specified id
    items.erase(std::remove_if(items.begin(), items.end(),
        [id](const std::unique_ptr<LibraryItem>& item) { return item->getId() == id; }),
        items.end());
}

// Find an item in the collection by id
LibraryItem* LibraryItemCollection::findItem(int id) {
    // Find the item with the specified id
    auto it = std::find_if(items.begin(), items.end(),
        [id](const std::unique_ptr<LibraryItem>& item) { return item->getId() == id; });
    
    // Return the raw pointer of the item if found, otherwise nullptr
    return (it != items.end()) ? it->get() : nullptr;
}

// Print details of all items in the collection
void LibraryItemCollection::printAllItems() const {
    for (const auto& item : items) {
        std::cout << *item << std::endl;
    }
}

// Print details of an item in the collection by id
void LibraryItemCollection::printItemDetails(int id) const {
    auto it = std::find_if(items.begin(), items.end(),
        [id](const std::unique_ptr<LibraryItem>& item) { return item->getId() == id; });
    
    if (it != items.end()) {
        std::cout << **it << std::endl;
    } else {
        std::cout << "Item not found." << std::endl;
    }
}

// Get a const reference to the vector of all items in the collection
const std::vector<std::unique_ptr<LibraryItem>>& LibraryItemCollection::getAllItems() const {
    return items;
}

// Overloaded insertion operator to print item details
std::ostream& operator<<(std::ostream& os, const LibraryItem& item) {
    os << "ID: " << item.getId() << ", Cost: $" << item.getCost()
       << ", Status: " << item.getStatusString() << ", Loan Period: " << item.getLoanPeriod() << " days";
    
    // Check the dynamic type of the item and append additional details accordingly
    if (const BookChild* book = dynamic_cast<const BookChild*>(&item)) {
        os << ", Type: Book, Title: " << book->getTitle() << ", Author: " << book->getAuthor();
    } else if (const AudioCD* cd = dynamic_cast<const AudioCD*>(&item)) {
        os << ", Type: AudioCD, Title: " << cd->getTitle() << ", Artist: " << cd->getArtist();
    } else if (const DVD* dvd = dynamic_cast<const DVD*>(&item)) {
        os << ", Type: DVD, Title: " << dvd->getTitle() << ", Studio: " << dvd->getStudio();
    }
    
    return os;
}

// Report an item as lost by id
void LibraryItemCollection::reportLost(int itemId) {
    LibraryItem* item = findItem(itemId);
    if (item) {
        item->reportLost(); // Mark the item as lost
        std::cout << "Item with ID " << itemId << " reported as lost.\n";
    } else {
        std::cout << "Item with ID " << itemId << " not found. Report lost operation failed.\n";
    }
}
