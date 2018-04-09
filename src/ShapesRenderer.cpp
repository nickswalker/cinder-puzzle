#include <puzzle/ShapesRenderer.h>
#include <cinder/gl/gl.h>
#include <puzzle/Rect.h>

using namespace cinder;
using namespace std;
namespace Puzzle {
    void Puzzle::ShapesRenderer::render(const vector<Puzzle::Fact::Ptr> &solution) {
        gl::clear(Color(0, 0.0f, 0.0f));

        vector<Color> colors;
        for (auto &color: color_map) {
            colors.push_back(color.second);
        }
        random_shuffle(colors.begin(), colors.end());
        int i = 0;
        for (auto &fact: solution) {

            if (auto rect = dynamic_pointer_cast<Rect>(fact)) {
                auto o_x = rect->x - 1;
                auto o_y = rect->y - 1;
                auto cinder_rect = Rectf(o_x * scale, o_y * scale, (o_x + rect->width) * scale,
                                         (o_y + rect->height) * scale);
                gl::color(colors.at(i));
                gl::drawSolidRect(cinder_rect);
                i++;
                i%=colors.size();
            }
        }

    }

}