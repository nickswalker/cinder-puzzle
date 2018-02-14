#ifndef PUZZLE_PUZZLE_H
#define PUZZLE_PUZZLE_H

#include <vector>
#include "Domain.h"
#include "Fact.h"
#include "Rule.h"

namespace Puzzle {

    class Puzzle {
        std::vector<Fact::Ptr> facts;
    public:
        Puzzle();

        void compose(const Domain &domain);

        void compose(const Fact::Ptr &fact);

        void compose(const Rule &fact);

        std::vector<Fact::Ptr> get_facts() const;
    };

}


#endif //PUZZLE_PUZZLE_H
