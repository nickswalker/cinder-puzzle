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
    gl::clear(Color::black());

    if (show_constraints) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (constraint_map.get()[(i - 1) + width * (j - 1)]) {
                    gl::color(Color::white());
                    int x_origin = (i - 1) * scale;
                    int y_origin = (j - 1) * scale;
                    gl::drawSolidTriangle({x_origin, y_origin}, ivec2(x_origin + scale, y_origin + scale),
                                          ivec2(x_origin + scale, y_origin));
                }
            }
        }
    }
    for (auto &fact: solution) {
        if (auto pixel_color = dynamic_pointer_cast<PixelColor>(fact)) {
            if (color_map.count(pixel_color->color) == 0) {
                cerr << "Unknown color " << pixel_color->color << endl;
                continue;
            }
            gl::color(color_map[pixel_color->color]);
            int x_origin = (pixel_color->x - 1) * scale;
            int y_origin = (pixel_color->y - 1) * scale;
            auto rect = Rectf(x_origin, y_origin, pixel_color->x * scale,
                              pixel_color->y * scale);
            gl::drawSolidRect(rect);


        }
    }

}

void Puzzle::PixelsRenderer::set_constraint_map(shared_ptr<int[]> constraint_map) {
    this->constraint_map = move(constraint_map);
}

void Puzzle::PixelsRenderer::set_canvas_size(size_t width, size_t height) {
    this->width = width;
    this->height = height;
}
