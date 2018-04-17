#ifndef PUZZLE_SHAPESRENDERER_H
#define PUZZLE_SHAPESRENDERER_H

#include <puzzle/Renderer.h>

#include <vector>
#include <map>
#include <utility>
#include <cinder/Cinder.h>
#include <cinder/Color.h>


namespace Puzzle {
    class ShapesRenderer : public Renderer {
    public:
        const std::map<std::string, ci::Color> color_map;
        explicit ShapesRenderer(std::map<std::string, ci::Color> color_map): color_map(std::move(color_map)) {};
        void render(const std::vector<Fact::Ptr> &solution) override;
    };
}


#endif
