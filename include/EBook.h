#pragma once

#include "Book.h"

class EBook : public Book {
private:
    std::string fileFormat;
    double fileSizeMB;

protected:
    void print(std::ostream& os) const override;

public:
    EBook(const std::string& title, const std::string& author, double basePrice,
          int stock, const std::string& fileFormat, double fileSizeMB);

    double calculateFinalPrice() const override;
    std::shared_ptr<Book> clone() const override;
};
