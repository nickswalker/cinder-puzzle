#include "puzzle/PixelsDomain.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <puzzle/Fact.h>
#include <vector>
#include <puzzle/RawFact.h>
#include <boost/make_shared.hpp>
#include <set>
#include <puzzle/Constant.h>
#include <puzzle/PixelColor.h>
#include <glm/detail/type_vec.hpp>

using namespace std;

namespace Puzzle {
    PixelsDomain::PixelsDomain(const size_t _width, const size_t _height, const vector<string> &colors) : width(_width),
                                                                                                          height(_height),
                                                                                                          colors(colors),
                                                                                                          constraints(
                                                                                                                  new int[
                                                                                                                  width *
                                                                                                                  height]) {
        ifstream domain_file("./domains/pixels.lp");
        stringstream buffer;
        buffer << domain_file.rdbuf();
        Fact::Ptr fact = make_shared<RawFact>(buffer.str());
        facts.emplace_back(fact);

        domain_file.close();
        fill_n(constraints.get(), width * height, 0);
    }

    vector<Fact::Ptr> PixelsDomain::get_facts() const {
        vector<Fact::Ptr> facts = this->facts;
        // Define the canvas size
        facts.emplace_back(make_shared<Constant>("n", width));
        facts.emplace_back(make_shared<Constant>("m", height));
        if (neighbors_different) {
            // TODO: Domain shouldn't know about ASP
            // In principle, the domain shouldn't care about how the instance is solved. It
            // should state facts and those facts are then realized in a form that a specific
            // solver can handle. RawFact is an expedient hack to avoid formally specifying
            // things like
            facts.emplace_back(make_shared<RawFact>(
                    ":- neighbor(A, B, C, D), pix(A, B), pix(C, D), cpix(Z, A, B), cpix(Z, C, D), col(Z)."));
        }
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                int constraint = constraints.get()[j * width + i];
                if (constraint != 0) {
                    auto color_str = colors[constraint - 1];
                    // Note that the domain is 1 indexed
                    auto color_pix = make_shared<PixelColor>(i + 1, j + 1, color_str);
                    facts.emplace_back(color_pix);
                }
            }
        }
        ostringstream s;
        s << "col((";
        for (int i = 0; i < colors.size(); i++) {
            s << colors[i];
            if (i != colors.size() - 1) {
                s << ";";
            }
        }

        s << ")).";
        facts.emplace_back(make_shared<RawFact>(s.str()));
        return facts;
    }

    void PixelsDomain::set_canvas_size(const size_t width, const size_t height) {
        this->width = width;
        this->height = height;
        constraints = shared_ptr<int[]>(new int[width * height]);
        fill_n(constraints.get(), width * height, 0);
    }

    vector<string> PixelsDomain::get_options() const {
        return vector<string>();
    }

    void PixelsDomain::constrain_pixel(uint32_t x, uint32_t y, const std::string &color) {
        auto find_result = find(colors.begin(), colors.end(), color);
        auto index = distance(colors.begin(), find_result);

        constraints.get()[y * width + x] = index;
    }

    void PixelsDomain::increment_constraint(uint32_t x, uint32_t y) {
        constraints.get()[y * width + x] = (constraints.get()[y * width + x] + 1) % colors.size();
    }

    void PixelsDomain::clear_constraint(uint32_t x, uint32_t y) {
        constraints.get()[y * width + x] = 0;
    }


    glm::ivec2 PixelsDomain::get_canvas_size() {
        return {width, height};
    }


}
