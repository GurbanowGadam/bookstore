#include "Order.h"

#include <iostream>

int Order::nextOrderId = 1;

Order::Order(const std::string& bookTitle, int quantity, double totalPrice)
    : id(nextOrderId++), bookTitle(bookTitle), quantity(quantity), totalPrice(totalPrice) {
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Order ID: " << order.id
       << ", Book: " << order.bookTitle
       << ", Quantity: " << order.quantity
       << ", Total price: " << order.totalPrice;

    return os;
}
