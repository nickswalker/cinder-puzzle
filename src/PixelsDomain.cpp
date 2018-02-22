#include "puzzle/PixelsDomain.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <puzzle/Fact.h>
#include <vector>
#include <puzzle/RawFact.h>
#include <boost/make_shared.hpp>
#include <set>

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
        fill_n(constraints, width * height, 0);
    }

    vector<Fact::Ptr> PixelsDomain::get_facts() const {
        vector<Fact::Ptr> facts = this->facts;
        // Define the canvas size
        ostringstream out;
        out << "#const n=" << this->width << ".";
        out << "#const m=" << this->height << ".";
        Fact::Ptr canvas_configuration = make_shared<RawFact>(out.str());
        facts.emplace_back(canvas_configuration);
        if (neighbors_different) {
            facts.emplace_back(make_shared<RawFact>(
                    ":- neighbor(A, B, C, D), pix(A, B), pix(C, D), cpix(Z, A, B), cpix(Z, C, D), col(Z)."));
        }
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                int constraint = constraints[j * width + i];
                if (constraint != 0) {
                    auto color_str = colors[constraint - 1];
                    ostringstream s;
                    // The domain is 0 indexed
                    s << "cpix(" << color_str << ", " << i + 1 << ", " << j + 1 << ").";
                    facts.emplace_back(make_shared<RawFact>(s.str()));
                }
            }
        }
        return facts;
    }

    void PixelsDomain::set_canvas_size(const size_t width, const size_t height) {
        this->width = width;
        this->height = height;
    }

    vector<string> PixelsDomain::get_options() const {
        return vector<string>();
    }

    void PixelsDomain::constrain_pixel(uint32_t x, uint32_t y, const std::string &color) {
        auto find_result = find(colors.begin(), colors.end(), color);
        auto index = distance(colors.begin(), find_result);

        constraints[y * width + x] = index;
    }

    void PixelsDomain::increment_constraint(uint32_t x, uint32_t y) {
        constraints[y * width + x] = (constraints[y * width + x] + 1) % colors.size();
    }

    void PixelsDomain::clear_constraint(uint32_t x, uint32_t y) {
        constraints[y * width + x] = 0;
    }

    PixelsDomain::~PixelsDomain() { delete[] constraints; }


}
