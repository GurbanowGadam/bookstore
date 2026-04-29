cmake_minimum_required(VERSION 3.10)

project(bookstore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bookstore
    main.cpp
    src/Book.cpp
    src/PrintedBook.cpp
    src/EBook.cpp
    src/AudioBook.cpp
    src/Bookstore.cpp
    src/Order.cpp
    src/BookstoreException.cpp
)

target_include_directories(bookstore PRIVATE include)
