#ifndef PUZZLE_TSPDOMAIN_H
#define PUZZLE_TSPDOMAIN_H


#include <puzzle/Domain.h>
#include <set>
#include <glm/detail/type_vec.hpp>

namespace Puzzle {
    class TSPDomain : public Domain {
        std::vector<Fact::Ptr> facts;

    public:
        std::vector<glm::ivec2> points;

        TSPDomain();

        ~TSPDomain();

        std::vector<Fact::Ptr> get_facts() const override;

        std::vector<std::string> get_options() const override;


    };
}

#endif //PUZZLE_TSPDOMAIN_H
