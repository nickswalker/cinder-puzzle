#ifndef PUZZLE_PIXELSDOMAIN_H
#define PUZZLE_PIXELSDOMAIN_H

#include <puzzle/Domain.h>
#include <set>
namespace Puzzle {
    class PixelsDomain : public Domain {
        std::vector<Fact::Ptr> facts;
        std::vector<std::string> colors;
        size_t width;
        size_t height;
        int *constraints;
    public:
        PixelsDomain(size_t _width, size_t _height, const std::vector<std::string> &colors);

        ~PixelsDomain();

        std::vector<Fact::Ptr> get_facts() const override;

        std::vector<std::string> get_options() const override;

        void set_canvas_size(const size_t width, const size_t height);

        void constrain_pixel(uint32_t x, uint32_t y, const std::string &color);

        bool neighbors_different = false;

        void increment_constraint(uint32_t x, uint32_t y);

        void clear_constraint(uint32_t x, uint32_t y);
    };
}

#endif //PUZZLE_PIXELSDOMAIN_H
