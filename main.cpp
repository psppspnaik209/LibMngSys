
//main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "LibraryItemCollection.h"
#include "PatronCollection.h"
#include "LoanCollection.h"
#include "BookChild.h"
#include "AudioCD.h"
#include "DVD.h"

using namespace std;

// Function to display the menu options
void displayMenu() {
    cout << "\n\n";
    cout << "  ooooo         o8o   .o8                                                     \n";
    cout << "  `888'         `\"'  \"888                                                    \n";
    cout << "    888         oooo   888oooo.  oooo d8b  .oooo.   oooo d8b oooo    ooo       \n";
    cout << "    888         `888   d88' `88b `888\"\"8P `P  )88b  `888\"\"8P  `88.  .8'       \n";
    cout << "    888          888   888   888  888      .oP\"888   888       `88..8'        \n";
    cout << "    888       o  888   888   888  888     d8(  888   888        `888'         \n";
    cout << "   o888ooooood8 o888o  `Y8bod8P' d888b    `Y888\"\"8o d888b        .8'          \n";
    cout << "                                                            .o..P'             \n";
    cout << "                                                            `Y8P'              \n";
    cout << "\n";
    // ASCII art made using (https://patorjk.com/software/taag/#p=display&f=Roman&t=Library%0A)

    cout << "1.  Add Item (Book/AudioCD/DVD)\n";
    cout << "2.  Edit Item\n";
    cout << "3.  Delete Item\n";
    cout << "4.  Find Item\n";
    cout << "5.  List All Items\n";
    cout << "6.  Add Patron\n";
    cout << "7.  Edit Patron\n";
    cout << "8.  Delete Patron\n";
    cout << "9.  Find Patron\n";
    cout << "10. List All Patrons\n";
    cout << "11. Check Out Item\n";
    cout << "12. Check In Item\n";
    cout << "13. List Overdue Items\n";
    cout << "14. List Items for Patron\n";
    cout << "15. Update Loan Status\n";
    cout << "16. Pay Fine\n";
    cout << "17. Report Lost Item\n";
    cout << "0.  Exit\n";
    cout << "Enter your choice: ";
}

// Function to load patron data from a CSV file into the PatronCollection
void loadPatrons(PatronCollection& patronCollection, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, fineBalance, currentBooksOut;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, fineBalance, ',');
        getline(ss, currentBooksOut, ',');

        // Create Patron object and add it to the collection
        Patron patron(name, stoi(id));
        patron.setFineBalance(stod(fineBalance));
        patron.setCurrentBooksOut(stoi(currentBooksOut));
        patronCollection.addPatron(patron);
    }

    file.close();
}

// Function to load loan data from a CSV file into the LoanCollection
void loadLoans(LoanCollection& loanCollection, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        stringstream ss(line);
        string loanId, bookId, patronId, dueDate, status;

        getline(ss, loanId, ',');
        getline(ss, bookId, ',');
        getline(ss, patronId, ',');
        getline(ss, dueDate, ',');
        getline(ss, status, ',');

        // Create Loan object and add it to the collection
        Loan loan(stoi(loanId), stoi(bookId), stoi(patronId));

        // Convert string to time_point
        tm tm = {};
        stringstream ss_date(dueDate);
        ss_date >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
        loan.setDueDate(mktime(&tm));

        if (status == "Overdue") {
            loan.setCurrentStatus(Loan::Status::Overdue);
        }

        loanCollection.addLoan(loan);
    }

    file.close();
}

// Function to load library item data from a CSV file into the LibraryItemCollection
void loadLibraryItems(LibraryItemCollection& itemCollection, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        stringstream ss(line);
        string id, type, cost, status, loanPeriod, title, authorArtist, isbnTracksRunTime, categoryGenreStudio, releaseDate;

        getline(ss, id, ',');
        getline(ss, type, ',');
        getline(ss, cost, ',');
        getline(ss, status, ',');
        getline(ss, loanPeriod, ',');
        getline(ss, title, ',');
        getline(ss, authorArtist, ',');
        getline(ss, isbnTracksRunTime, ',');
        getline(ss, categoryGenreStudio, ',');
        getline(ss, releaseDate, ',');

        LibraryItem::Status itemStatus = LibraryItem::Status::In;
        if (status == "Out") itemStatus = LibraryItem::Status::Out;
        else if (status == "Lost") itemStatus = LibraryItem::Status::Lost;

        if (type == "Book") {
            BookChild::Category category;
            if (categoryGenreStudio == "Fiction") category = BookChild::Category::Fiction;
            else if (categoryGenreStudio == "SciFi") category = BookChild::Category::SciFi;
            else if (categoryGenreStudio == "History") category = BookChild::Category::History;
            else category = BookChild::Category::Biography;

            itemCollection.addItem(make_unique<BookChild>(stoi(id), stod(cost), stoi(loanPeriod), authorArtist, title, isbnTracksRunTime, category));
        }
        else if (type == "AudioCD") {
            AudioCD::Genre genre;
            if (categoryGenreStudio == "Pop") genre = AudioCD::Genre::Pop;
            else if (categoryGenreStudio == "ClassicRock") genre = AudioCD::Genre::ClassicRock;
            else if (categoryGenreStudio == "Classical") genre = AudioCD::Genre::Classical;
            else if (categoryGenreStudio == "Jazz") genre = AudioCD::Genre::Jazz;
            else genre = AudioCD::Genre::NewAge;

            itemCollection.addItem(make_unique<AudioCD>(stoi(id), stod(cost), stoi(loanPeriod), authorArtist, title, stoi(isbnTracksRunTime), releaseDate, genre));
        }
        else if (type == "DVD") {
            DVD::Category category;
            if (categoryGenreStudio == "Action") category = DVD::Category::Action;
            else if (categoryGenreStudio == "SciFi") category = DVD::Category::SciFi;
            else category = DVD::Category::Drama;

            itemCollection.addItem(make_unique<DVD>(stoi(id), stod(cost), stoi(loanPeriod), title, category, stoi(isbnTracksRunTime), categoryGenreStudio, releaseDate));
        }
    }

    file.close();
}

// Function to save patron data from PatronCollection to a CSV file
void savePatrons(const PatronCollection& patronCollection, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }

    file << "ID,Name,FineBalance,CurrentBooksOut\n";
    for (const auto& patron : patronCollection.getAllPatrons()) {
        file << patron.getIdNumber() << ","
             << patron.getName() << ","
             << patron.getFineBalance() << ","
             << patron.getCurrentBooksOut() << "\n";
    }

    file.close();
}

// Function to save loan data from LoanCollection to a CSV file
void saveLoans(const LoanCollection& loanCollection, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }

    file << "LoanID,BookID,PatronID,DueDate,Status\n";
    for (const auto& loan : loanCollection.getAllLoans()) {
        time_t dueDate = loan.getDueDate();
        file << loan.getLoanId() << ","
             << loan.getBookId() << ","
             << loan.getPatronId() << ","
             << put_time(localtime(&dueDate), "%Y-%m-%d %H:%M:%S") << ","
             << loan.getStatusString() << "\n";
    }

    file.close();
}

// Function to save library item data from LibraryItemCollection to a CSV file
void saveLibraryItems(const LibraryItemCollection& itemCollection, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }

    file << "ID,Type,Cost,Status,LoanPeriod,Title,Author/Artist,ISBN/Tracks/RunTime,Category/Genre/Studio,ReleaseDate\n";
    for (const auto& item : itemCollection.getAllItems()) {
        file << item->getId() << ",";
        
        if (const BookChild* book = dynamic_cast<const BookChild*>(item.get())) {
            file << "Book," << book->getCost() << "," << book->getStatusString() << "," << book->getLoanPeriod() << ","
                 << book->getTitle() << "," << book->getAuthor() << "," << book->getIsbnNumber() << "," << book->getCategoryString() << ",\n";
        }
        else if (const AudioCD* cd = dynamic_cast<const AudioCD*>(item.get())) {
            file << "AudioCD," << cd->getCost() << "," << cd->getStatusString() << "," << cd->getLoanPeriod() << ","
                 << cd->getTitle() << "," << cd->getArtist() << "," << cd->getNumberOfTracks() << ","
                 << cd->getGenreString() << "," << cd->getReleaseDate() << "\n";
        }
        else if (const DVD* dvd = dynamic_cast<const DVD*>(item.get())) {
            file << "DVD," << dvd->getCost() << "," << dvd->getStatusString() << "," << dvd->getLoanPeriod() << ","
                 << dvd->getTitle() << ",," << dvd->getRunTime() << ","
                 << dvd->getStudio() << "," << dvd->getReleaseDate() << "\n";
        }
    }

    file.close();
}


// Main function to run the library management system
int main() {
    // Initialize collections for library items, patrons, and loans
    LibraryItemCollection itemCollection;
    PatronCollection patronCollection;
    LoanCollection loanCollection(itemCollection, patronCollection);

    // Load data from CSV files into respective collections
    loadLibraryItems(itemCollection, "library_items.csv");
    loadPatrons(patronCollection, "patrons.csv");
    loadLoans(loanCollection, "loans.csv");

    int choice;
    do {
        // Display menu options and get user's choice
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: { // Add Item (Book/AudioCD/DVD)
                // Prompt user for item type
                int itemType;
                cout << "Enter item type (1: Book, 2: AudioCD, 3: DVD): ";
                cin >> itemType;

                // Get common item details
                int id, loanPeriod;
                double cost;
                string title;

                cout << "Enter item details:\n";
                cout << "ID: ";
                cin >> id;
                cout << "Cost: ";
                cin >> cost;
                cout << "Loan Period (days): ";
                cin >> loanPeriod;
                cin.ignore();
                cout << "Title: ";
                getline(cin, title);

                if (itemType == 1) { // Book
                    // Get book-specific details
                    string author, isbn;
                    int category;
                    cout << "Author: ";
                    getline(cin, author);
                    cout << "ISBN: ";
                    getline(cin, isbn);
                    cout << "Category (0: Biography, 1: Fiction, 2: SciFi, 3: History): ";
                    cin >> category;
                    // Create and add book to collection
                    itemCollection.addItem(make_unique<BookChild>(id, cost, loanPeriod, author, title, isbn, static_cast<BookChild::Category>(category)));
                }
                else if (itemType == 2) { // AudioCD
                    // Get AudioCD-specific details
                    string artist, releaseDate;
                    int tracks, genre;
                    cout << "Artist: ";
                    getline(cin, artist);
                    cout << "Number of Tracks: ";
                    cin >> tracks;
                    cin.ignore();
                    cout << "Release Date: ";
                    getline(cin, releaseDate);
                    cout << "Genre (0: Pop, 1: ClassicRock, 2: Classical, 3: Christian, 4: Jazz, 5: NewAge): ";
                    cin >> genre;
                    // Create and add AudioCD to collection
                    itemCollection.addItem(make_unique<AudioCD>(id, cost, loanPeriod, artist, title, tracks, releaseDate, static_cast<AudioCD::Genre>(genre)));
                }
                else if (itemType == 3) { // DVD
                    // Get DVD-specific details
                    int category, runTime;
                    string studio, releaseDate;
                    cout << "Category (0: Action, 1: SciFi, 2: Drama): ";
                    cin >> category;
                    cout << "Run Time (minutes): ";
                    cin >> runTime;
                    cin.ignore();
                    cout << "Studio: ";
                    getline(cin, studio);
                    cout << "Release Date: ";
                    getline(cin, releaseDate);
                    // Create and add DVD to collection
                    itemCollection.addItem(make_unique<DVD>(id, cost, loanPeriod, title, static_cast<DVD::Category>(category), runTime, studio, releaseDate));
                }

                cout << "Item added successfully.\n";
                // Save updated item collection to file
                saveLibraryItems(itemCollection, "library_items.csv");
                break;
            }
            case 2: // Edit Item
            {
                // Prompt for item ID to edit
                int itemId;
                cout << "Enter item ID to edit: ";
                cin >> itemId;
                cin.ignore();

                // Find the item in the collection
                LibraryItem* item = itemCollection.findItem(itemId);

                if (item) {
                    // Determine the type of item and call the appropriate edit function
                    if (auto* book = dynamic_cast<BookChild*>(item)) {
                        // Edit Book
                        string title, author, isbn;
                        double cost;
                        int loanPeriod, category;

                        // Prompt for new details, update if provided
                        cout << "Enter new title (" << book->getTitle() << "): ";
                        getline(cin, title);
                        if (!title.empty()) book->setTitle(title);

                        cout << "Enter new author (" << book->getAuthor() << "): ";
                        getline(cin, author);
                        if (!author.empty()) book->setAuthor(author);

                        cout << "Enter new ISBN (" << book->getIsbnNumber() << "): ";
                        getline(cin, isbn);
                        if (!isbn.empty()) book->setIsbnNumber(isbn);

                        cout << "Enter new cost (" << book->getCost() << "): ";
                        cin >> cost;
                        cin.ignore();
                        if (cost >= 0) book->setCost(cost);

                        cout << "Enter new loan period (" << book->getLoanPeriod() << "): ";
                        cin >> loanPeriod;
                        cin.ignore();
                        if (loanPeriod > 0) book->setLoanPeriod(loanPeriod);

                        cout << "Enter new category (0: Biography, 1: Fiction, 2: SciFi, 3: History) (" << book->getCategoryString() << "): ";
                        cin >> category;
                        cin.ignore();
                        if (category >= 0 && category <= 3) book->setCategory(static_cast<BookChild::Category>(category));

                        cout << "Book details updated successfully.\n";
                    } else if (auto* audioCD = dynamic_cast<AudioCD*>(item)) {
                        // Edit AudioCD
                        string title, artist, releaseDate;
                        int tracks, genre;
                        double cost;
                        int loanPeriod;

                        // Prompt for new details, update if provided
                        cout << "Enter new title (" << audioCD->getTitle() << "): ";
                        getline(cin, title);
                        if (!title.empty()) audioCD->setTitle(title);

                        cout << "Enter new artist (" << audioCD->getArtist() << "): ";
                        getline(cin, artist);
                        if (!artist.empty()) audioCD->setArtist(artist);

                        cout << "Enter new number of tracks (" << audioCD->getNumberOfTracks() << "): ";
                        cin >> tracks;
                        cin.ignore();
                        if (tracks > 0) audioCD->setNumberOfTracks(tracks);

                        cout << "Enter new release date (" << audioCD->getReleaseDate() << "): ";
                        getline(cin, releaseDate);
                        if (!releaseDate.empty()) audioCD->setReleaseDate(releaseDate);

                        cout << "Enter new genre (0: Pop, 1: ClassicRock, 2: Classical, 3: Christian, 4: Jazz, 5: NewAge) (" << audioCD->getGenreString() << "): ";
                        cin >> genre;
                        cin.ignore();
                        if (genre >= 0 && genre <= 5) audioCD->setGenre(static_cast<AudioCD::Genre>(genre));

                        cout << "Enter new cost (" << audioCD->getCost() << "): ";
                        cin >> cost;
                        cin.ignore();
                        if (cost >= 0) audioCD->setCost(cost);

                        cout << "Enter new loan period (" << audioCD->getLoanPeriod() << "): ";
                        cin >> loanPeriod;
                        cin.ignore();
                        if (loanPeriod > 0) audioCD->setLoanPeriod(loanPeriod);

                        cout << "AudioCD details updated successfully.\n";
                    } else if (auto* dvd = dynamic_cast<DVD*>(item)) {
                        // Edit DVD
                        string title, studio, releaseDate;
                        int runTime, category;
                        double cost;
                        int loanPeriod;

                        // Prompt for new details, update if provided
                        cout << "Enter new title (" << dvd->getTitle() << "): ";
                        getline(cin, title);
                        if (!title.empty()) dvd->setTitle(title);

                        cout << "Enter new run time (" << dvd->getRunTime() << "): ";
                        cin >> runTime;
                        cin.ignore();
                        if (runTime > 0) dvd->setRunTime(runTime);

                        cout << "Enter new studio (" << dvd->getStudio() << "): ";
                        getline(cin, studio);
                        if (!studio.empty()) dvd->setStudio(studio);

                        cout << "Enter new release date (" << dvd->getReleaseDate() << "): ";
                        getline(cin, releaseDate);
                        if (!releaseDate.empty()) dvd->setReleaseDate(releaseDate);

                        cout << "Enter new category (0: Action, 1: SciFi, 2: Drama) (" << dvd->getCategoryString() << "): ";
                        cin >> category;
                        cin.ignore();
                        if (category >= 0 && category <= 2) dvd->setCategory(static_cast<DVD::Category>(category));

                        cout << "Enter new cost (" << dvd->getCost() << "): ";
                        cin >> cost;
                        cin.ignore();
                        if (cost >= 0) dvd->setCost(cost);

                        cout << "Enter new loan period (" << dvd->getLoanPeriod() << "): ";
                        cin >> loanPeriod;
                        cin.ignore();
                        if (loanPeriod > 0) dvd->setLoanPeriod(loanPeriod);

                        cout << "DVD details updated successfully.\n";
                    }

                    // Save the updated item collection to file
                    saveLibraryItems(itemCollection, "library_items.csv");
                } else {
                    cout << "Item not found.\n";
                }
                break;
            }
           case 3: { // Delete Item
                // Prompt for item ID to delete
                int id;
                cout << "Enter item ID to delete: ";
                cin >> id;
                // Delete item and save updated collection
                itemCollection.deleteItem(id);
                cout << "Item deleted successfully.\n";
                saveLibraryItems(itemCollection, "library_items.csv");
                break;
            }
            case 4: { // Find Item
                // Prompt for item ID to find
                int id;
                cout << "Enter item ID to find: ";
                cin >> id;
                // Find and display item if found
                LibraryItem* item = itemCollection.findItem(id);
                if (item) {
                    cout << *item << endl;
                } else {
                    cout << "Item not found.\n";
                }
                break;
            }
            case 5: // List All Items
                // Display all items in the collection
                itemCollection.printAllItems();
                break;
            case 6: { // Add Patron
                // Prompt for patron details
                string name;
                int id;
                cout << "Enter patron details:\n";
                cin.ignore();
                cout << "Name: ";
                getline(cin, name);
                cout << "ID: ";
                cin >> id;
                // Add patron and save updated collection
                patronCollection.addPatron(Patron(name, id));
                cout << "Patron added successfully.\n";
                savePatrons(patronCollection, "patrons.csv");
                break;
            }
            case 7: { // Edit Patron
                // Prompt for patron ID to edit
                int patronId;
                cout << "Enter patron ID: ";
                cin >> patronId;
                
                // Find the patron in the collection
                Patron* patron = patronCollection.findPatron(patronId);
                
                if (patron) {
                    // Display current details
                    cout << "Current details of patron " << patron->getName() << ":" << endl;
                    cout << "ID: " << patron->getIdNumber() << ", Name: " << patron->getName() << ", Fine Balance: $" << patron->getFineBalance() << endl;
                    
                    // Prompt for new details
                    string newName;
                    double newFineBalance;
                    
                    cout << "Enter new name (or leave blank to keep current): ";
                    cin.ignore(); // Ignore newline character from previous cin
                    getline(cin, newName);
                    
                    // Update name if provided
                    if (!newName.empty()) {
                        patron->setName(newName);
                    }
                    
                    cout << "Enter new fine balance (or enter 0 to clear): $";
                    cin >> newFineBalance;
                    
                    // Update fine balance if valid
                    if (newFineBalance >= 0) {
                        patron->setFineBalance(newFineBalance);
                    } else {
                        cout << "Invalid input. Fine balance remains unchanged." << endl;
                    }
                    
                    // Save changes
                    savePatrons(patronCollection, "patrons.csv");
                    cout << "Patron details updated successfully." << endl;
                } else {
                    cout << "Patron not found." << endl;
                }
                break;
            }

            case 8: { // Delete Patron
                // Prompt for patron ID to delete
                int id;
                cout << "Enter patron ID to delete: ";
                cin >> id;
                // Delete patron and save updated collection
                patronCollection.deletePatron(id);
                cout << "Patron deleted successfully.\n";
                savePatrons(patronCollection, "patrons.csv");
                break;
            }
            case 9: { // Find Patron
                // Prompt for patron ID to find
                int id;
                cout << "Enter patron ID to find: ";
                cin >> id;
                // Find and display patron if found
                Patron* patron = patronCollection.findPatron(id);
                if (patron) {
                    cout << *patron << endl;
                } else {
                    cout << "Patron not found.\n";
                }
                break;
            }
            case 10: // List All Patrons
                // Display all patrons in the collection
                patronCollection.printAllPatrons();
                break;
            case 11: { // Check Out Item
                // Prompt for item and patron IDs
                int itemId, patronId;
                cout << "Enter item ID: ";
                cin >> itemId;
                cout << "Enter patron ID: ";
                cin >> patronId;
                // Process check out and save updated collections
                loanCollection.checkOutItem(itemId, patronId);
                saveLibraryItems(itemCollection, "library_items.csv");
                savePatrons(patronCollection, "patrons.csv");
                saveLoans(loanCollection, "loans.csv");
                break;
            }
            case 12: { // Check In Item
                // Prompt for loan ID
                int loanId;
                cout << "Enter loan ID: ";
                cin >> loanId;
                // Process check in and save updated collections
                loanCollection.checkInItem(loanId);
                saveLibraryItems(itemCollection, "library_items.csv");
                savePatrons(patronCollection, "patrons.csv");
                saveLoans(loanCollection, "loans.csv");
                break;
            }
            case 13: // List Overdue Items
                // Display all overdue items
                loanCollection.listAllOverdue();
                break;
            case 14: { // List Items Checked Out by Patron
                // Prompt for patron ID
                int patronId;
                cout << "Enter patron ID: ";
                cin >> patronId;
                // Display items checked out by the patron
                loanCollection.listItemsForPatron(patronId);
                break;
            }
            case 15: { // Update Loan Status
                // Update the status of all loans
                loanCollection.updateLoanStatuses();
                cout << "Loan statuses updated.\n";
                // Save updated loan collection
                saveLoans(loanCollection, "loans.csv");
                break;
            }
            case 16: { // Pay Fine
                // Prompt for patron ID and fine amount
                int patronId;
                double amount;
                cout << "Enter patron ID: ";
                cin >> patronId;
                Patron* patron = patronCollection.findPatron(patronId);
                if (patron) {
                    // Display current fine balance and prompt for payment amount
                    cout << "Current fine balance: $" << patron->getFineBalance() << endl;
                    cout << "Enter amount to pay: ";
                    cin >> amount;
                    if (amount > 0) {
                        // Process payment and update patron record
                        patron->payFine(amount);
                        cout << "Fine paid successfully. New balance: $" << patron->getFineBalance() << endl;
                        savePatrons(patronCollection, "patrons.csv");
                    } else {
                        cout << "Invalid amount entered.\n";
                    }
                } else {
                    cout << "Patron not found.\n";
                }
                break;
            }
            case 17: // Report Lost Item
            {
                // Prompt for item ID of the lost item
                int itemId;
                cout << "Enter item ID of the lost item: ";
                cin >> itemId;

                // Find the item in the collection
                LibraryItem* item = itemCollection.findItem(itemId);

                if (item) {
                    // Find the loan associated with this item
                    const auto& loans = loanCollection.getAllLoans();
                    auto loanIt = std::find_if(loans.begin(), loans.end(),
                        [itemId](const Loan& loan) { return loan.getBookId() == itemId; });

                    if (loanIt != loans.end()) {
                        int patronId = loanIt->getPatronId();
                        Patron* patron = patronCollection.findPatron(patronId);

                        if (patron) {
                            // Report the item as lost
                            item->setStatus(LibraryItem::Status::Lost);
                            item->reportLost();

                            // Add fine to patron's account
                            double fine = item->getCost();
                            patron->addFine(fine);

                            // Decrease the number of books checked out by the patron
                            patron->decrementBooksOut();

                            // Remove the loan
                            loanCollection.checkInItem(loanIt->getLoanId());

                            // Save the updated collections to files
                            saveLibraryItems(itemCollection, "library_items.csv");
                            savePatrons(patronCollection, "patrons.csv");
                            saveLoans(loanCollection, "loans.csv");

                            cout << "Item reported as lost successfully. Fine of $" << fine << " added to patron's account.\n";
                        } else {
                            cout << "Patron not found.\n";
                        }
                    } else {
                        cout << "This item is not currently checked out.\n";
                    }
                } else {
                    cout << "Item not found.\n";
                }
                break;
            }
            case 0:
                // Exit the program
                cout << "Exiting...\n";
                break;
            default:
                // Handle invalid menu choices
                cout << "Invalid choice. Please enter a number from the menu.\n";
                break;
        }
    } while (choice != 0);
    
    cout << "Exited.. ";
    return 0;
}
