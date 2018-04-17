#ifndef PUZZLE_PIXELSRENDERER_H
#define PUZZLE_PIXELSRENDERER_H

#include "Renderer.h"

namespace Puzzle {
    class PixelsRenderer : public Renderer {
    public:
        std::map<std::string, cinder::Color> color_map;

        explicit PixelsRenderer(std::map<std::string, cinder::Color> color_map);

        void render(const std::vector<Fact::Ptr> &solution) override;

        void set_constraint_map(std::shared_ptr<int[]> shared_ptr);

        std::shared_ptr<int[]> constraint_map;

        void set_canvas_size(size_t width, size_t height);

        size_t width;
        size_t height;
        bool show_constraints;
    };
}


#endif //PUZZLE_PIXELSRENDERER_H
