#ifndef PUZZLE_CONSTANT_H
#define PUZZLE_CONSTANT_H

#include <puzzle/Fact.h>

namespace Puzzle {
    class Constant : public Fact {
    public:
        Constant(std::string name, std::string value);

        Constant(std::string name, int value);

        typedef std::shared_ptr<Constant> Ptr;
        std::string name;
        std::string value;

        std::string to_string();
    };
}


#endif
