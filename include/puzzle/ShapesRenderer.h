#ifndef PUZZLE_SHAPESRENDERER_H
#define PUZZLE_SHAPESRENDERER_H

#include <puzzle/Renderer.h>
#include <vector>

namespace Puzzle {
    class ShapesRenderer : public Renderer {
    public:
        void render(const std::vector<Fact::Ptr> &solution) override;
    };
}


#endif
