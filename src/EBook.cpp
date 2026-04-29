#include "EBook.h"

#include "BookstoreException.h"

#include <iostream>
#include <memory>

EBook::EBook(const std::string& title, const std::string& author, double basePrice,
             int stock, const std::string& fileFormat, double fileSizeMB)
    : Book(title, author, basePrice, stock), fileFormat(fileFormat), fileSizeMB(fileSizeMB) {
    if (fileFormat.empty()) {
        throw InvalidBookDataException("E-book file format cannot be empty.");
    }
    if (fileSizeMB <= 0) {
        throw InvalidBookDataException("E-book file size must be positive.");
    }
}

double EBook::calculateFinalPrice() const {
    return basePrice * 0.85;
}

std::shared_ptr<Book> EBook::clone() const {
    // We use clone() for deep copy.
    return std::make_shared<EBook>(*this);
}

void EBook::print(std::ostream& os) const {
    Book::print(os);
    os << ", Type: E-book"
       << ", Format: " << fileFormat
       << ", File size: " << fileSizeMB << " MB";
}
