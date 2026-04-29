#pragma once

#include <stdexcept>
#include <string>

class BookstoreException : public std::runtime_error {
public:
    explicit BookstoreException(const std::string& message);
};

class InvalidBookDataException : public BookstoreException {
public:
    explicit InvalidBookDataException(const std::string& message);
};

class BookNotFoundException : public BookstoreException {
public:
    explicit BookNotFoundException(const std::string& message);
};

class NotEnoughStockException : public BookstoreException {
public:
    explicit NotEnoughStockException(const std::string& message);
};
