#ifndef PUZZLE_RECT_H
#define PUZZLE_RECT_H

#include <puzzle/Fact.h>

namespace Puzzle {
    class Rect : public Fact {
    public:
        typedef std::shared_ptr<Rect> Ptr;

        size_t width;
        size_t height;
        size_t x;
        size_t y;

        explicit Rect(size_t width, size_t height, size_t x, size_t y) : width(width), height(height), x(x), y(y) {};

        std::string to_string() override {
            std::ostringstream out;
            out << "rect(width=" << width << " height=" << height << " x=" << x << " y=" << y << ").";
            return out.str();

        }
    };
}
#endif //PUZZLE_RECT_H
