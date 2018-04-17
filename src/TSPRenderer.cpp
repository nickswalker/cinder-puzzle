//
// Created by nwalker on 4/4/18.
//

#include <puzzle/TSPRenderer.h>
#include <puzzle/CycleEdge.h>
#include <cinder/gl/gl.h>
#include <puzzle/FactN.h>

using namespace cinder;
using namespace std;

void Puzzle::TSPRenderer::render(const std::vector<Puzzle::Fact::Ptr> &solution) {
    gl::clear(Color::black());
    for (const auto &center: points) {
        gl::color(Color::black());
        gl::drawSolidCircle(center, 2 * scale);
        gl::color(Color::white());
        gl::drawSolidCircle(center, 5 * scale);
    }
    vector<Color> colors;
    for (auto &pair: color_map) {
        colors.emplace_back(pair.second);
    }

    gl::lineWidth(100.f);
    for (auto &fact: solution) {
        if (auto cycle_edge = dynamic_pointer_cast<CycleEdge>(fact)) {
            auto color = colors.at(cycle_edge->x % colors.size());
            gl::color(color);
            gl::drawLine(points.at(cycle_edge->x - 1), points.at(cycle_edge->y - 1));
        } else if (auto total_cost = dynamic_pointer_cast<Fact1<uint32_t>>(fact)) {
            cout << "Total cost: " << total_cost->value << endl;
        }

    }
}

void Puzzle::TSPRenderer::set_nodes(const std::vector<glm::ivec2> &points) {
    this->points = points;
}

void Puzzle::TSPRenderer::clear() {
    gl::clear();
}
