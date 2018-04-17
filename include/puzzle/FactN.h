#ifndef PUZZLE_FACT1_H
#define PUZZLE_FACT1_H

#include <utility>
#include <sstream>
#include "Fact.h"

namespace Puzzle {
    template <typename T>
    struct Fact1 : public Fact {
    public:
        typedef std::shared_ptr<Fact1> Ptr;
        T value;
        std::string name;

        Fact1(std::string name, T value) : name(std::move(name)), value(value) {};

        std::string to_string() override {
            std::ostringstream out;
            out << name << "(" << value << ").";
            return out.str();
        }
    };

    template <typename T, typename U>
    struct Fact2 : public Fact {
    public:
        typedef std::shared_ptr<Fact2> Ptr;
        T first;
        U second;
        std::string name;

        Fact2(std::string name, T first, U second) : name(std::move(name)), first(first), second(second) {};

        std::string to_string() override {
            std::ostringstream out;
            out << name << "(" << first << ", " << second << ").";
            return out.str();
        }
    };
}

#endif //PUZZLE_FACT1_H
