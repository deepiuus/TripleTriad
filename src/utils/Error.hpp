/*
** EPITECH PROJECT, 2025
** TripleTriad [WSL: Debian]
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <string>

namespace triad
{
    class Error : public std::exception {
        public:
            Error(const std::string &message) : _message(message) {}
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };
}

#endif
