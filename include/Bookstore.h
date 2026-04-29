#pragma once

#include "Book.h"
#include "Order.h"

#include <memory>
#include <string>
#include <vector>

class Bookstore {
private:
    std::string name;
    std::vector<std::shared_ptr<Book>> books;

public:
    explicit Bookstore(const std::string& name);
    Bookstore(const Bookstore& other);

    Bookstore& operator=(Bookstore other);

    friend void swap(Bookstore& first, Bookstore& second) noexcept;

    void addBook(std::shared_ptr<Book> book);
    std::shared_ptr<Book> findBookById(int id) const;
    void showBooks() const;
    Order sellBook(int id, int quantity);
    void showPrintedBookShippingInfo() const;
};
