#include "puzzle/PixelsDomain.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <puzzle/Fact.h>
#include <vector>
#include <puzzle/RawFact.h>
#include <boost/make_shared.hpp>

using namespace std;

namespace Puzzle {
    PixelsDomain::PixelsDomain(const size_t _width, const size_t _height) : width(_width), height(_height) {
        ifstream domain_file("./domains/pixels.lp");
        stringstream buffer;
        buffer << domain_file.rdbuf();
        cout << buffer.str();
        Fact::Ptr fact = make_shared<RawFact>(buffer.str());
        facts.emplace_back(fact);

        domain_file.close();
    }

    std::vector<Fact::Ptr> PixelsDomain::get_facts() const {
        vector<Fact::Ptr> facts = this->facts;
        // Define the canvas size
        ostringstream out;
        out << "#const n=" << this->width << ".";
        out << "#const m=" << this->height << ".";
        Fact::Ptr canvas_configuration = make_shared<RawFact>(out.str());
        facts.emplace_back(canvas_configuration);
        return facts;
    }

    void PixelsDomain::set_canvas_size(const size_t width, const size_t height) {
        this->width = width;
        this->height = height;
    }

    vector<string> PixelsDomain::get_options() const {
        return vector<string>();
    }

}
