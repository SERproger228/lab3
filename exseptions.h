#pragma once

#include <stdexcept>
#include <string>

class IndexOutOfRange : public std::out_of_range {
public:
    explicit IndexOutOfRange(const std::string& msg = "Index out of range")
        : std::out_of_range(msg) {}
};

class InvalidArgument : public std::invalid_argument {
public:
    explicit InvalidArgument(const std::string& msg = "Invalid argument")
        : std::invalid_argument(msg) {}
};
