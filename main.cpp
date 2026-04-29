#include "AudioBook.h"
#include "Bookstore.h"
#include "BookstoreException.h"
#include "EBook.h"
#include "PrintedBook.h"

#include <iostream>
#include <limits>
#include <memory>

namespace {
int readInt(const std::string& prompt) {
    int value = 0;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value) {
            return value;
        }

        std::cout << "Invalid number. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void showMenu() {
    std::cout << "\nMenu\n"
              << "1. Show all books\n"
              << "2. Sell a book\n"
              << "3. Find a book by id\n"
              << "4. Show printed book shipping information\n"
              << "0. Exit\n";
}

void sellBook(Bookstore& bookstore) {
    int id = readInt("Book id: ");
    int quantity = readInt("Quantity: ");

    Order order = bookstore.sellBook(id, quantity);
    std::cout << order << '\n';
}

void findBook(const Bookstore& bookstore) {
    int id = readInt("Book id: ");
    std::cout << *bookstore.findBookById(id) << '\n';
}

void runMenu(Bookstore& bookstore) {
    bool running = true;

    while (running) {
        showMenu();
        int option = readInt("Choose an option: ");

        try {
            switch (option) {
            case 1:
                bookstore.showBooks();
                break;
            case 2:
                sellBook(bookstore);
                break;
            case 3:
                findBook(bookstore);
                break;
            case 4:
                bookstore.showPrintedBookShippingInfo();
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Unknown option.\n";
                break;
            }
        } catch (const BookstoreException& exception) {
            std::cout << "Bookstore error: " << exception.what() << '\n';
        }
    }
}
}

int main() {
    try {
        Bookstore bookstore("Bookstore");

        auto printedBook = std::make_shared<PrintedBook>(
            "Clean Code Basics", "John Smith", 40.0, 5, 250, 1.2);
        auto ebook = std::make_shared<EBook>(
            "Modern C++ Notes", "Alice Brown", 30.0, 10, "PDF", 4.5);
        auto audioBook = std::make_shared<AudioBook>(
            "OOP Stories", "Mark Green", 25.0, 3, 180, "Emma White");
        auto printedBook2 = std::make_shared<PrintedBook>(
            "Design Patterns Intro", "Robert Martin", 55.0, 4, 320, 1.5);
        auto printedBook3 = std::make_shared<PrintedBook>(
            "Algorithms Practice", "Laura Johnson", 48.0, 6, 410, 1.8);
        auto ebook2 = std::make_shared<EBook>(
            "Git Quick Guide", "Daniel White", 18.0, 20, "EPUB", 2.1);
        auto ebook3 = std::make_shared<EBook>(
            "Database Essentials", "Maria Evans", 35.0, 8, "PDF", 6.2);
        auto audioBook2 = std::make_shared<AudioBook>(
            "Software Testing Talks", "Helen Brooks", 28.0, 5, 240, "Paul Carter");
        auto audioBook3 = std::make_shared<AudioBook>(
            "Clean Architecture Audio", "Adam Clark", 32.0, 2, 300, "Nora Hill");

        bookstore.addBook(printedBook);
        bookstore.addBook(ebook);
        bookstore.addBook(audioBook);
        bookstore.addBook(printedBook2);
        bookstore.addBook(printedBook3);
        bookstore.addBook(ebook2);
        bookstore.addBook(ebook3);
        bookstore.addBook(audioBook2);
        bookstore.addBook(audioBook3);

        std::cout << "Initial books are created from the example data in main.cpp.\n";
        bookstore.showBooks();
        runMenu(bookstore);
    } catch (const BookstoreException& exception) {
        std::cout << "Bookstore error: " << exception.what() << '\n';
    } catch (const std::exception& exception) {
        std::cout << "Unexpected error: " << exception.what() << '\n';
    }

    return 0;
}
