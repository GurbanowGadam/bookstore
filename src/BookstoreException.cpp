#include "BookstoreException.h"

BookstoreException::BookstoreException(const std::string& message)
    : std::runtime_error(message) {
}

InvalidBookDataException::InvalidBookDataException(const std::string& message)
    : BookstoreException(message) {
}

BookNotFoundException::BookNotFoundException(const std::string& message)
    : BookstoreException(message) {
}

NotEnoughStockException::NotEnoughStockException(const std::string& message)
    : BookstoreException(message) {
}
