#ifndef PUZZLE_DOMAIN_H
#define PUZZLE_DOMAIN_H

#include <vector>
#include <string>
#include <puzzle/Fact.h>

namespace Puzzle {
    class Domain {
    public:
        virtual std::vector<Fact::Ptr> get_facts() const = 0;

        virtual std::vector<std::string> get_options() const = 0;

    };

}


#endif //PUZZLE_DOMAIN_H
