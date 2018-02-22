#ifndef PUZZLE_RENDERER_H
#define PUZZLE_RENDERER_H

#include "Fact.h"

namespace Puzzle {
    class Renderer {
    public:
        uint8_t scale = 1;

        // TODO: Pass in the GL context somehow?
        virtual void render(const std::vector<Fact::Ptr> &solution) = 0;

    };
}

#endif //PUZZLE_RENDERER_H
