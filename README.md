# Bookstore

## Problem Statement

A bookstore needs a small application for managing the books available for sale. The store sells multiple types of books: printed books, e-books, and audio books. All books have common information such as title, author, base price, and stock, but each type also has specific data.

The application must keep all books in one collection, display the available books, find a book by id, and sell a selected quantity. When a book is sold, the stock is updated and the total order price is calculated using the final price of that specific book type. The program must also handle invalid data, missing books, and insufficient stock through custom exceptions.

## Solution Overview

The solution is built around an abstract base class named `Book`. The classes `PrintedBook`, `EBook`, and `AudioBook` inherit from `Book` and implement their own final price calculation.

The `Bookstore` class contains a `std::vector<std::shared_ptr<Book>>`, so all derived book types can be stored in the same collection. Virtual functions are called through base-class pointers, which allows the program to use polymorphism when displaying books and calculating prices.

The program starts with several example books created in `main.cpp`. A small menu allows the user to list books, sell a book, find a book by id, and show shipping information for printed books.

## Main Features

- Show all books from the bookstore.
- Sell a book by id and quantity.
- Update stock after each sale.
- Create an `Order` object after a successful sale.
- Find a book by id.
- Show shipping costs only for printed books.
- Report errors with custom exception classes.

## Menu Options

```text
1. Show all books
2. Sell a book
3. Find a book by id
4. Show printed book shipping information
0. Exit
```

The menu uses only short inputs such as option number, book id, and quantity. The example book data is not entered manually from the keyboard.

## OOP Concepts Used

- Encapsulation: class attributes are private or protected.
- Composition: a `Bookstore` has a collection of books.
- Inheritance: `PrintedBook`, `EBook`, and `AudioBook` inherit from `Book`.
- Polymorphism: final prices and printed details are resolved through virtual functions.
- Pure virtual functions: `calculateFinalPrice()` and `clone()` are declared in `Book`.
- Virtual destructor: `Book` has a virtual destructor.
- Non-virtual interface: `display()` calls the protected virtual `print()` function.
- Constructor chaining: derived constructors call the `Book` constructor.
- Smart pointers: the project uses `std::shared_ptr<Book>`.
- STL containers: the project uses `std::vector`.
- Downcasting: `std::dynamic_pointer_cast` is used to access printed-book shipping data.
- Copy support: `Bookstore` implements copy constructor, assignment operator, and copy-and-swap.
- Custom exceptions: invalid data, missing books, and insufficient stock use distinct exception classes.
- Static fields: book ids and order ids are generated with static class fields.
- Const correctness: read-only methods are marked with `const`.
- Operator overloading: `operator<<` prints `Book` and `Order` objects.

## Class Structure

- `Book`: abstract base class for all book types.
- `PrintedBook`: stores page count and weight; final price includes shipping.
- `EBook`: stores file format and file size; final price applies a discount.
- `AudioBook`: stores duration and narrator; final price depends on duration.
- `Bookstore`: manages the collection of books and handles sale operations.
- `Order`: stores the result of a sale.
- `BookstoreException`: base exception class for bookstore-specific errors.

## File Structure

```text
bookstore/
|
|-- README.md
|-- CMakeLists.txt
|-- main.cpp
|
|-- include/
|   |-- Book.h
|   |-- PrintedBook.h
|   |-- EBook.h
|   |-- AudioBook.h
|   |-- Bookstore.h
|   |-- Order.h
|   |-- BookstoreException.h
|
|-- src/
|   |-- Book.cpp
|   |-- PrintedBook.cpp
|   |-- EBook.cpp
|   |-- AudioBook.cpp
|   |-- Bookstore.cpp
|   |-- Order.cpp
|   |-- BookstoreException.cpp
```

## Example Data

The example book data is created directly in `main.cpp`. This keeps the project simple and avoids file parsing code that was not needed for the current version.

## Build and Run

From the project folder, run:

```bash
cmake -S . -B build
cmake --build build
./build/bookstore
```

## Bibliografie

- https://github.com/GFA03/oop
