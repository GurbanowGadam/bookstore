#include "Bookstore.h"

#include "BookstoreException.h"
#include "PrintedBook.h"

#include <iostream>
#include <memory>
#include <utility>

Bookstore::Bookstore(const std::string& name)
    : name(name) {
    if (name.empty()) {
        throw InvalidBookDataException("Bookstore name cannot be empty.");
    }
}

Bookstore::Bookstore(const Bookstore& other)
    : name(other.name) {
    for (const auto& book : other.books) {
        // clone() creates a new object with the same data.
        books.push_back(book->clone());
    }
}

Bookstore& Bookstore::operator=(Bookstore other) {
    swap(*this, other);
    return *this;
}

void swap(Bookstore& first, Bookstore& second) noexcept {
    using std::swap;
    swap(first.name, second.name);
    swap(first.books, second.books);
}

void Bookstore::addBook(std::shared_ptr<Book> book) {
    if (!book) {
        throw InvalidBookDataException("Cannot add an empty book.");
    }

    books.push_back(book);
}

std::shared_ptr<Book> Bookstore::findBookById(int id) const {
    for (const auto& book : books) {
        if (book->getId() == id) {
            return book;
        }
    }

    throw BookNotFoundException("Book with id " + std::to_string(id) + " was not found.");
}

void Bookstore::showBooks() const {
    std::cout << "\nBooks from " << name << ":\n";

    if (books.empty()) {
        std::cout << "No books in the bookstore.\n";
        return;
    }

    for (const auto& book : books) {
        // This function uses polymorphism.
        std::cout << *book << '\n';
    }
}

Order Bookstore::sellBook(int id, int quantity) {
    if (quantity <= 0) {
        throw InvalidBookDataException("Quantity must be positive.");
    }

    auto book = findBookById(id);

    if (quantity > book->getStock()) {
        throw NotEnoughStockException("Not enough stock for book: " + book->getTitle());
    }

    book->reduceStock(quantity);
    double totalPrice = book->calculateFinalPrice() * quantity;

    return Order(book->getTitle(), quantity, totalPrice);
}

void Bookstore::showPrintedBookShippingInfo() const {
    std::cout << "\nPrinted book shipping information:\n";

    for (const auto& book : books) {
        auto printedBook = std::dynamic_pointer_cast<PrintedBook>(book);

        if (printedBook) {
            // This cast is safe because we check the result.
            std::cout << printedBook->getTitle()
                      << " has shipping cost "
                      << printedBook->getShippingCost() << '\n';
        }
    }
}
