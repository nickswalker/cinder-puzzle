#include <puzzle/ShapesRenderer.h>
#include <cinder/gl/gl.h>
#include <puzzle/Rect.h>

using namespace cinder;
using namespace std;
namespace Puzzle {
    void Puzzle::ShapesRenderer::render(const std::vector<Puzzle::Fact::Ptr> &solution) {
        gl::clear(Color(0, 0.0f, 0.0f));

        for (auto &fact: solution) {
            if (auto rect = dynamic_pointer_cast<Rect>(fact)) {
                auto cinder_rect = Rectf((rect->x - 1) * scale, (rect->y - 1) * scale, (rect->x + rect->width) * scale,
                                         (rect->y + rect->height) * scale);
                gl::drawSolidRect(cinder_rect);
            }
        }

    }

}