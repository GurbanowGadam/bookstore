#pragma once

#include "Book.h"

class PrintedBook : public Book {
private:
    int pages;
    double weight;

protected:
    void print(std::ostream& os) const override;

public:
    PrintedBook(const std::string& title, const std::string& author, double basePrice,
                int stock, int pages, double weight);

    double calculateFinalPrice() const override;
    std::shared_ptr<Book> clone() const override;
    double getShippingCost() const;
};
