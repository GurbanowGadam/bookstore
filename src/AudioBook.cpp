#include "AudioBook.h"

#include "BookstoreException.h"

#include <iostream>
#include <memory>

AudioBook::AudioBook(const std::string& title, const std::string& author, double basePrice,
                     int stock, int durationMinutes, const std::string& narrator)
    : Book(title, author, basePrice, stock),
      durationMinutes(durationMinutes),
      narrator(narrator) {
    if (durationMinutes <= 0) {
        throw InvalidBookDataException("Audio book duration must be positive.");
    }
    if (narrator.empty()) {
        throw InvalidBookDataException("Audio book narrator cannot be empty.");
    }
}

double AudioBook::calculateFinalPrice() const {
    return basePrice + durationMinutes * 0.01;
}

std::shared_ptr<Book> AudioBook::clone() const {
    // We use clone() for deep copy.
    return std::make_shared<AudioBook>(*this);
}

void AudioBook::print(std::ostream& os) const {
    Book::print(os);
    os << ", Type: Audio book"
       << ", Duration: " << durationMinutes << " minutes"
       << ", Narrator: " << narrator;
}
