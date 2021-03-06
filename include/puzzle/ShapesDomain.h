#ifndef PUZZLE_SHAPESDOMAIN_H
#define PUZZLE_SHAPESDOMAIN_H

#include <puzzle/Domain.h>
#include <glm/vec2.hpp>

namespace Puzzle {
    class ShapesDomain : public Domain {
        std::vector<Fact::Ptr> facts;
        size_t width;
        size_t height;

    public:
        ShapesDomain(size_t width, size_t height);

        std::vector<Fact::Ptr> get_facts() const;

        std::vector<std::string> get_options() const;

        void set_canvas_size(size_t width, size_t height);

        void set_num_shapes(size_t num_shapes);

        glm::ivec2 get_canvas_size();

        size_t num_shapes;
    };
}


#endif //PUZZLE_SHAPESDOMAIN_H
