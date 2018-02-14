#ifndef PUZZLE_FACT_H
#define PUZZLE_FACT_H

#include <boost/shared_ptr.hpp>

namespace Puzzle {
    class Fact {
    public:
        virtual ~Fact() = default;

        typedef std::shared_ptr<Fact> Ptr;
    };
}

#endif //PUZZLE_FACT_H
