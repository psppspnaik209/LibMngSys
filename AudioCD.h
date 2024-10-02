// AudioCD.h
#ifndef AUDIO_CD_H
#define AUDIO_CD_H

#include "LibraryItem.h" // Include base class header file
#include <string>

class AudioCD : public LibraryItem {
private:
    std::string artist;         // Artist of the audio CD
    std::string title;          // Title of the audio CD
    int numberOfTracks;         // Number of tracks on the audio CD
    std::string releaseDate;    // Release date of the audio CD

public:
    // Genre enumeration for different music genres
    enum class Genre { 
        Pop,            // Pop genre
        ClassicRock,    // Classic Rock genre
        Classical,      // Classical genre
        Christian,      // Christian genre
        Jazz,           // Jazz genre
        NewAge          // New Age genre
    };
    Genre genre; // Genre of the audio CD

    // Constructor with parameters to initialize the AudioCD object
    AudioCD(int id, double cost, int loanPeriod, std::string artist, std::string title,
            int numberOfTracks, std::string releaseDate, Genre genre);

    // Accessor functions to retrieve private member variables
    std::string getArtist() const;       // Getter for artist
    std::string getTitle() const;        // Getter for title
    int getNumberOfTracks() const;       // Getter for number of tracks
    std::string getReleaseDate() const;  // Getter for release date
    std::string getGenreString() const;  // Getter to convert Genre enum to string

    // Mutator functions to modify private member variables
    void setArtist(const std::string& artist);          // Setter for artist
    void setTitle(const std::string& title);            // Setter for title
    void setNumberOfTracks(int numberOfTracks);         // Setter for number of tracks
    void setReleaseDate(const std::string& releaseDate);// Setter for release date
    void setGenre(Genre genre);                         // Setter for genre
};

#endif // AUDIO_CD_H
