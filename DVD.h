// DVD.h
#ifndef DVD_H
#define DVD_H

#include "LibraryItem.h" // Include base class header file
#include <string>

class DVD : public LibraryItem {
private:
    std::string title;       // Title of the DVD
    int runTime;             // Runtime of the DVD in minutes
    std::string studio;      // Studio that produced the DVD
    std::string releaseDate; // Release date of the DVD

public:
    // Category enumeration for different DVD categories
    enum class Category { 
        Action,   // Action category
        SciFi,    // Science Fiction category
        Drama     // Drama category
    };
    Category category; // Category of the DVD

    // Constructor with parameters to initialize the DVD object
    DVD(int id, double cost, int loanPeriod, std::string title, Category category,
        int runTime, std::string studio, std::string releaseDate);

    // Accessor functions to retrieve private member variables
    std::string getTitle() const;          // Getter for title
    std::string getCategoryString() const; // Getter to convert Category enum to string
    int getRunTime() const;                // Getter for runtime
    std::string getStudio() const;         // Getter for studio
    std::string getReleaseDate() const;    // Getter for release date

    // Mutator functions to modify private member variables
    void setTitle(const std::string& title);        // Setter for title
    void setCategory(Category category);            // Setter for category
    void setRunTime(int runTime);                   // Setter for runtime
    void setStudio(const std::string& studio);      // Setter for studio
    void setReleaseDate(const std::string& releaseDate); // Setter for release date
};

#endif // DVD_H
