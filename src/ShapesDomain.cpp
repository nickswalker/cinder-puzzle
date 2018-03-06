#include "puzzle/ShapesDomain.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <puzzle/Fact.h>
#include <vector>
#include <puzzle/RawFact.h>
#include <boost/make_shared.hpp>
#include <set>
#include <puzzle/Constant.h>

using namespace std;

namespace Puzzle {
    ShapesDomain::ShapesDomain(const size_t _width, const size_t _height) : width(_width),
                                                                            height(_height) {
        ifstream domain_file("./domains/shapes.lp");
        stringstream buffer;
        buffer << domain_file.rdbuf();
        Fact::Ptr fact = make_shared<RawFact>(buffer.str());
        facts.emplace_back(fact);

        domain_file.close();
    }

    vector<Fact::Ptr> ShapesDomain::get_facts() const {
        vector<Fact::Ptr> facts = this->facts;
        // Define the canvas size
        facts.emplace_back(make_shared<Constant>("n", width));
        facts.emplace_back(make_shared<Constant>("m", height));

        return facts;
    }

    void ShapesDomain::set_canvas_size(const size_t width, const size_t height) {
        this->width = width;
        this->height = height;
    }

    vector<string> ShapesDomain::get_options() const {
        return vector<string>();
    }

}