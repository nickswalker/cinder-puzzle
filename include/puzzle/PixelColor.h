#ifndef PUZZLE_PIXELCOLOR_H
#define PUZZLE_PIXELCOLOR_H

#include <puzzle/Fact.h>
#include <sstream>

namespace Puzzle {
    struct PixelColor : public Fact {
    public:
        typedef std::shared_ptr<PixelColor> Ptr;
        uint32_t x;
        uint32_t y;
        std::string color;

        PixelColor(uint32_t x, uint32_t y, const std::string color) : x(x), y(y), color(color) {};

        std::string to_string() {
            std::ostringstream out;
            out << "cpix(" << x << ", " << y << ", " << color << ").";
            return out.str();
        }
    };
}

#endif //PUZZLE_PIXELCOLOR_H
