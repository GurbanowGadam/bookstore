#include "Book.h"

#include "BookstoreException.h"

#include <iostream>

int Book::nextId = 1;

Book::Book(const std::string& title, const std::string& author, double basePrice, int stock)
    : id(nextId++), title(title), author(author), basePrice(basePrice), stock(stock) {
    if (title.empty()) {
        throw InvalidBookDataException("Book title cannot be empty.");
    }
    if (author.empty()) {
        throw InvalidBookDataException("Book author cannot be empty.");
    }
    if (basePrice <= 0) {
        throw InvalidBookDataException("Book price must be positive.");
    }
    if (stock < 0) {
        throw InvalidBookDataException("Book stock cannot be negative.");
    }
}

Book::Book(const Book& other)
    : id(other.id),
      title(other.title),
      author(other.author),
      basePrice(other.basePrice),
      stock(other.stock) {
}

Book::~Book() = default;

int Book::getId() const {
    return id;
}

std::string Book::getTitle() const {
    return title;
}

int Book::getStock() const {
    return stock;
}

void Book::reduceStock(int quantity) {
    if (quantity <= 0) {
        throw InvalidBookDataException("Quantity must be positive.");
    }
    if (quantity > stock) {
        throw NotEnoughStockException("Not enough stock for this book.");
    }

    stock -= quantity;
}

void Book::display(std::ostream& os) const {
    print(os);
}

void Book::print(std::ostream& os) const {
    os << "ID: " << id
       << ", Title: " << title
       << ", Author: " << author
       << ", Base price: " << basePrice
       << ", Final price: " << calculateFinalPrice()
       << ", Stock: " << stock;
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    book.display(os);
    return os;
}
