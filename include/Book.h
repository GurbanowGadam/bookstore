#pragma once

#include <iosfwd>
#include <memory>
#include <string>

class Book {
private:
    static int nextId;
    const int id;

protected:
    std::string title;
    std::string author;
    double basePrice;
    int stock;

    virtual void print(std::ostream& os) const;

public:
    Book(const std::string& title, const std::string& author, double basePrice, int stock);
    Book(const Book& other);
    virtual ~Book();

    int getId() const;
    std::string getTitle() const;
    int getStock() const;

    void reduceStock(int quantity);

    virtual double calculateFinalPrice() const = 0;
    virtual std::shared_ptr<Book> clone() const = 0;

    void display(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const Book& book);
