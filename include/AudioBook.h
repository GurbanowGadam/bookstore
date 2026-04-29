#pragma once

#include "Book.h"

class AudioBook : public Book {
private:
    int durationMinutes;
    std::string narrator;

protected:
    void print(std::ostream& os) const override;

public:
    AudioBook(const std::string& title, const std::string& author, double basePrice,
              int stock, int durationMinutes, const std::string& narrator);

    double calculateFinalPrice() const override;
    std::shared_ptr<Book> clone() const override;
};
