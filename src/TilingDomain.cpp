#include "puzzle/TilingDomain.h"
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
#include <puzzle/PixelsDomain.h>
#include <glm/geometric.hpp>

using namespace std;

namespace Puzzle {
    TilingDomain::TilingDomain(const size_t width, const size_t height) : width(width), height(height) {
        ifstream domain_file("./domains/tiling.lp");
        stringstream buffer;
        buffer << domain_file.rdbuf();
        Fact::Ptr fact = make_shared<RawFact>(buffer.str());
        facts.emplace_back(fact);

        domain_file.close();
    }

    vector<Fact::Ptr> TilingDomain::get_facts() const {
        vector<Fact::Ptr> facts = this->facts;
        facts.emplace_back(make_shared<Constant>("n", width));
        facts.emplace_back(make_shared<Constant>("m", height));
        return facts;
    }

    void TilingDomain::set_canvas_size(const size_t width, const size_t height) {
        this->width = width;
        this->height = height;
    }

    vector<string> TilingDomain::get_options() const {
        return vector<string>();
    }

    TilingDomain::~TilingDomain() {

    }


}
