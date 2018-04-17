#ifndef PUZZLE_TILINGRENDERER_H
#define PUZZLE_TILINGRENDERER_H


#include <cinder/Color.h>
#include <map>
#include <utility>
#include "Renderer.h"

namespace Puzzle {
    class TilingRenderer : public Renderer {
        int solutions_seen;
    public:
        std::map<std::string, cinder::Color> color_map;

        explicit TilingRenderer(std::map<std::string, cinder::Color> color_map) : color_map(std::move(color_map)),
                                                                                  solutions_seen(0) {

        }

        void render(const std::vector<Fact::Ptr> &solution) override;


    };
}


#endif
