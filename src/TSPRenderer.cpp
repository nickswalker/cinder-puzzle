//
// Created by nwalker on 4/4/18.
//

#include <puzzle/TSPRenderer.h>
#include <puzzle/CycleEdge.h>
#include <cinder/gl/gl.h>

using namespace cinder;
using namespace std;

void Puzzle::TSPRenderer::render(const std::vector<Puzzle::Fact::Ptr> &solution) {
    gl::clear(Color(0, 0.0f, 0.0f));

    gl::color(255, 255, 255);
    for (const auto &center: points) {
        gl::drawSolidCircle(center, 5);
    }
    gl::lineWidth(5);
    for (auto &fact: solution) {
        if (auto cycle_edge = dynamic_pointer_cast<CycleEdge>(fact)) {
            gl::drawLine(points.at(cycle_edge->x - 1), points.at(cycle_edge->y - 1));

        }
    }
}

void Puzzle::TSPRenderer::set_nodes(const std::vector<glm::ivec2> &points) {
    this->points = points;
}
