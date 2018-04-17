#ifndef PUZZLE_TILINGDOMAIN_H
#define PUZZLE_TILINGDOMAIN_H


#include <puzzle/Domain.h>
#include <set>
#include <glm/detail/type_vec.hpp>

namespace Puzzle {
    class TilingDomain : public Domain {
        std::vector<Fact::Ptr> facts;

    public:

        TilingDomain(const size_t width, const size_t height);

        ~TilingDomain();

        std::vector<Fact::Ptr> get_facts() const override;

        std::vector<std::string> get_options() const override;


        bool minimize_cost;

        void set_canvas_size(const size_t width, const size_t height);

        size_t width;
        size_t height;
    };
}

#endif