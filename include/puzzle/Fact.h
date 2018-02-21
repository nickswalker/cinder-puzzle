#ifndef PUZZLE_FACT_H
#define PUZZLE_FACT_H

#include <boost/shared_ptr.hpp>

namespace Puzzle {
    class Fact {
    public:
        typedef std::shared_ptr<Fact> Ptr;

        virtual ~Fact() = default;

        virtual std::string to_string() = 0;


    };
}

#endif //PUZZLE_FACT_H
