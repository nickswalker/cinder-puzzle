#include <puzzle/ShapesRenderer.h>
#include <cinder/gl/gl.h>
#include <puzzle/Rect.h>

using namespace cinder;
using namespace std;
namespace Puzzle {
    void Puzzle::ShapesRenderer::render(const vector<Puzzle::Fact::Ptr> &solution) {
        gl::clear(Color::black());
        int x_off = 300;
        int y_off = 100;


        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                gl::color(Color::white());
                gl::drawSolidCircle({x_off + i * scale, y_off + j * scale}, 0.1 * scale);
            }
        }
        int i = 0;
        cout << endl << endl;
        for (auto &fact: solution) {
            if (auto rect = dynamic_pointer_cast<Rect>(fact)) {
                cout << rect->to_string() << endl;
                auto o_x = rect->x - 1;
                auto o_y = rect->y - 1;
                auto cinder_rect = Rectf(x_off + o_x * scale, y_off + o_y * scale, x_off + (o_x + rect->width) * scale,
                                         y_off + (o_y + rect->height) * scale);
                gl::color(colors.at(i));
                gl::drawSolidRect(cinder_rect);
                i++;
                i %= colors.size();
            }
        }

    }

    void ShapesRenderer::set_canvas_size(size_t width, size_t height) {
        this->width = width;
        this->height = height;
    }

}