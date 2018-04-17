#include <puzzle/TilingRenderer.h>
#include <puzzle/CycleEdge.h>
#include <cinder/gl/gl.h>
#include <puzzle/FactN.h>

using namespace cinder;
using namespace std;

void Puzzle::TilingRenderer::render(const std::vector<Puzzle::Fact::Ptr> &solution) {
    vector<Color> colors;
    for (auto &pair: color_map) {
        colors.emplace_back(pair.second);
    }
    auto color = colors.at(solutions_seen % colors.size());
    gl::color(color);
    gl::lineWidth(100);
    for (auto &fact: solution) {
        if (auto covered = dynamic_pointer_cast<Puzzle::Fact3<uint32_t, uint32_t, uint32_t >>(fact)) {
            cout << "hi" << endl;
        }

    }
}

