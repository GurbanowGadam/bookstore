#include "PrintedBook.h"

#include "BookstoreException.h"

#include <iostream>
#include <memory>

PrintedBook::PrintedBook(const std::string& title, const std::string& author, double basePrice,
                         int stock, int pages, double weight)
    : Book(title, author, basePrice, stock), pages(pages), weight(weight) {
    if (pages <= 0) {
        throw InvalidBookDataException("Printed book pages must be positive.");
    }
    if (weight <= 0) {
        throw InvalidBookDataException("Printed book weight must be positive.");
    }
}

double PrintedBook::calculateFinalPrice() const {
    return basePrice + getShippingCost();
}

std::shared_ptr<Book> PrintedBook::clone() const {
    // We use clone() for deep copy.
    return std::make_shared<PrintedBook>(*this);
}

double PrintedBook::getShippingCost() const {
    return 5.0 + weight * 0.5;
}

void PrintedBook::print(std::ostream& os) const {
    Book::print(os);
    os << ", Type: Printed book"
       << ", Pages: " << pages
       << ", Weight: " << weight
       << ", Shipping cost: " << getShippingCost();
}
