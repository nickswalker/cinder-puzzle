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
        int width;
        int height;
    public:
        const std::map<std::string, ci::Color> color_map;
        std::vector<ci::Color> colors;

        explicit ShapesRenderer(std::map<std::string, ci::Color> color_map) : color_map(std::move(color_map)) {
            for (auto &color: this->color_map) {
                colors.push_back(color.second);
            }
            //random_shuffle(colors.begin(), colors.end());
        };
        void render(const std::vector<Fact::Ptr> &solution) override;

        void set_canvas_size(size_t width, size_t height);


    };
}


#endif
