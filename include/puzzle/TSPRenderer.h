#ifndef PUZZLE_TSPRENDERER_H
#define PUZZLE_TSPRENDERER_H


#include <cinder/Color.h>
#include <map>
#include "Renderer.h"

namespace Puzzle {
    class TSPRenderer : public Renderer {
        std::vector<glm::ivec2> points;
    public:
        std::map<std::string, cinder::Color> color_map;

        explicit TSPRenderer() {

        }

        void render(const std::vector<Fact::Ptr> &solution) override;

        void set_nodes(const std::vector<glm::ivec2> &points);

    };
}


#endif //PUZZLE_TSPRENDERER_H
