#ifndef PUZZLE_RAWFACT_H
#define PUZZLE_RAWFACT_H

#include <string>
#include <utility>
#include "Fact.h"

namespace Puzzle {
    class RawFact : public Fact {
    public:
        typedef std::shared_ptr<RawFact> Ptr;
        const std::string fact;

        explicit RawFact(const std::string &raw_fact) : fact(std::move(raw_fact)) {}

        ~RawFact() = default;;

    };
}
#endif //PUZZLE_RAWFACT_H
