#include <cinder/gl/wrapper.h>
#include <puzzle/PixelColor.h>
#include <cinder/gl/gl.h>

#include <utility>
#include <cinder/app/MouseEvent.h>
#include "puzzle/PixelsRenderer.h"

using namespace cinder;
using namespace std;


Puzzle::PixelsRenderer::PixelsRenderer(map<string, Color> color_map) : color_map(move(color_map)) {

}

void Puzzle::PixelsRenderer::render(const vector<Fact::Ptr> &solution) {
    gl::clear(Color(0, 0.0f, 0.0f));

    for (auto &fact: solution) {
        if (auto pixel_color = dynamic_pointer_cast<PixelColor>(fact)) {
            if (color_map.count(pixel_color->color) == 0) {
                cerr << "Unknown color " << pixel_color->color << endl;
                continue;
            }
            gl::color(color_map[pixel_color->color]);
            auto rect = Rectf((pixel_color->x - 1) * scale, (pixel_color->y - 1) * scale, pixel_color->x * scale,
                              pixel_color->y * scale);
            gl::drawSolidRect(rect);
        }
    }

}
