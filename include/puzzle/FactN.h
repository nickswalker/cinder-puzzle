#ifndef PUZZLE_FACT1_H
#define PUZZLE_FACT1_H

#include <utility>
#include <sstream>
#include "Fact.h"

namespace Puzzle {
    template<typename T>
    struct Fact1 : public Fact {
    public:
        typedef std::shared_ptr<Fact1<T>> Ptr;
        T value;
        std::string name;

        Fact1(std::string name, T value) : name(std::move(name)), value(value) {};

        std::string to_string() override {
            std::ostringstream out;
            out << name << "(" << value << ").";
            return out.str();
        }
    };

    template<typename T, typename U>
    struct Fact2 : public Fact {
    public:
        typedef std::shared_ptr<Fact2<T, U>> Ptr;
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

    template<typename T, typename U, typename V>
    struct Fact3 : public Fact {
    public:
        typedef std::shared_ptr<Fact3<T, U, V>> Ptr;
        T first;
        U second;
        V third;
        std::string name;

        Fact3(std::string name, T first, U second, V third) : name(std::move(name)), first(first), second(second),
                                                              third(third) {};

        std::string to_string() override {
            std::ostringstream out;
            out << name << "(" << first << ", " << second << ", " << third << ").";
            return out.str();
        }
    };
}

#endif //PUZZLE_FACT1_H
