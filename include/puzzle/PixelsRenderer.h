#ifndef PUZZLE_PIXELSRENDERER_H
#define PUZZLE_PIXELSRENDERER_H

#include "Renderer.h"

namespace Puzzle {
    class PixelsRenderer : public Renderer {
    public:
        std::map<std::string, cinder::Color> color_map;

        explicit PixelsRenderer(std::map<std::string, cinder::Color> color_map);

        void render(const std::vector<Fact::Ptr> &solution);
    };
}


#endif //PUZZLE_PIXELSRENDERER_H
