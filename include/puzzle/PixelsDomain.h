#ifndef PUZZLE_PIXELSDOMAIN_H
#define PUZZLE_PIXELSDOMAIN_H

#include <puzzle/Domain.h>

namespace Puzzle {
    class PixelsDomain : public Domain {
        std::vector<Fact::Ptr> facts;
        size_t width;
        size_t height;
    public:
        PixelsDomain(size_t _width, size_t _height);

        std::vector<Fact::Ptr> get_facts() const override;

        std::vector<std::string> get_options() const override;

        void set_canvas_size(const size_t width, const size_t height);


    };
}

#endif //PUZZLE_PIXELSDOMAIN_H
