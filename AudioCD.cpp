// AudioCD.cpp
#include "AudioCD.h"

// Constructor initializing AudioCD with parameters and passing id, cost, loanPeriod to base class
AudioCD::AudioCD(int id, double cost, int loanPeriod, std::string artist, std::string title,
                 int numberOfTracks, std::string releaseDate, Genre genre)
    : LibraryItem(id, cost, loanPeriod), // Initialize base class LibraryItem
      artist(artist),                   // Initialize member variables
      title(title),
      numberOfTracks(numberOfTracks),
      releaseDate(releaseDate),
      genre(genre) {}

// Getters for retrieving private member variables
std::string AudioCD::getArtist() const { return artist; }
std::string AudioCD::getTitle() const { return title; }
int AudioCD::getNumberOfTracks() const { return numberOfTracks; }
std::string AudioCD::getReleaseDate() const { return releaseDate; }

// Converts Genre enum to string representation
std::string AudioCD::getGenreString() const {
    switch (genre) {
        case Genre::Pop: return "Pop";
        case Genre::ClassicRock: return "Classic Rock";
        case Genre::Classical: return "Classical";
        case Genre::Christian: return "Christian";
        case Genre::Jazz: return "Jazz";
        case Genre::NewAge: return "New Age";
        default: return "Unknown";
    }
}

// Setters for modifying private member variables
void AudioCD::setArtist(const std::string& artist) { this->artist = artist; }
void AudioCD::setTitle(const std::string& title) { this->title = title; }
void AudioCD::setNumberOfTracks(int numberOfTracks) { this->numberOfTracks = numberOfTracks; }
void AudioCD::setReleaseDate(const std::string& releaseDate) { this->releaseDate = releaseDate; }
void AudioCD::setGenre(Genre genre) { this->genre = genre; }
