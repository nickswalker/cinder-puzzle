#include "puzzle/TSPDomain.h"
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
    TSPDomain::TSPDomain() {
        ifstream domain_file("./domains/tsp.lp");
        stringstream buffer;
        buffer << domain_file.rdbuf();
        Fact::Ptr fact = make_shared<RawFact>(buffer.str());
        facts.emplace_back(fact);

        domain_file.close();
    }

    vector<Fact::Ptr> TSPDomain::get_facts() const {
        vector<Fact::Ptr> facts = this->facts;

        {
            ostringstream s;
            s << "node(1.." << points.size() << ").";
            auto nodes = make_shared<RawFact>(s.str());
            facts.emplace_back(nodes);
        }

        for (int i = 0; i < points.size(); i++) {
            for (int j = 0; j < points.size(); j++) {
                // Only the top left of the adjacency matrix
                if (i == j) {
                    continue;
                }
                glm::fvec2 diff = points.at(i) - points.at(j);
                auto distance = (int) glm::length(diff);
                {
                    ostringstream s;
                    s << "cost(" << i + 1 << ", " << j + 1 << ", " << distance << ").";
                    auto cost = make_shared<RawFact>(s.str());
                    facts.emplace_back(cost);
                }
                {
                    ostringstream s;
                    s << "edge(" << i + 1 << ", " << j + 1 << ").";
                    auto cost = make_shared<RawFact>(s.str());
                    facts.emplace_back(cost);
                }
            }

        }

        return facts;
    }

    void PixelsDomain::set_canvas_size(const size_t width, const size_t height) {
        this->width = width;
        this->height = height;
    }

    vector<string> TSPDomain::get_options() const {
        return vector<string>();
    }


}
