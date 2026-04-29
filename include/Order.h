#pragma once

#include <iosfwd>
#include <string>

class Order {
private:
    static int nextOrderId;
    const int id;
    std::string bookTitle;
    int quantity;
    double totalPrice;

public:
    Order(const std::string& bookTitle, int quantity, double totalPrice);

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};
