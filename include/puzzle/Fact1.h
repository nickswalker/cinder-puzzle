#ifndef PUZZLE_FACT1_H
#define PUZZLE_FACT1_H


#include "Fact.h"

namespace Puzzle {
    struct Fact1 : public Fact {
    public:
        typedef std::shared_ptr<Fact1> Ptr;
        uint32_t value;

        Fact1(uint32_t value) : value(value) {};

        std::string to_string() {
            std::ostringstream out;
            out << "Fact1(" << value << ").";
            return out.str();
        }
    };
}

#endif //PUZZLE_FACT1_H
