#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <puzzle/ASPSolver.h>
#include <puzzle/PixelsDomain.h>
#include <puzzle/Puzzle.h>
#include <puzzle/PixelsRenderer.h>
#include <puzzle/PixelColor.h>
#include <map>
#include <functional>
#include <puzzle/TSPRenderer.h>
#include <puzzle/TSPDomain.h>
#include <puzzle/CycleEdge.h>
#include <puzzle/FactN.h>
#include <puzzle_demos/Colors.h>
#include <puzzle_demos/PuzzleDemoApp.h>

using namespace ci;
using namespace ci::app;
using namespace std;


class TSPDemo : public PuzzleDemos::PuzzleDemoApp {
public:

    int last_x = 0;
    int last_y = 0;

    vector<ivec2> circle_centers;

    void setup() override;

    void mouseDown(MouseEvent event) override;

    void draw() override;

};

void TSPDemo::setup() {
    PuzzleDemos::PuzzleDemoApp::setup();

    solution_span = 1000;
    vector<string> color_strings;
    renderer = new Puzzle::TSPRenderer(PuzzleDemos::Color::get_solarized());

    renderer->scale = 4;
    domain = new Puzzle::TSPDomain();

    auto tsp_renderer = (Puzzle::TSPRenderer *) renderer;
    auto tsp_domain = (Puzzle::TSPDomain *) domain;
    tsp_domain->minimize_cost = true;

    parser = [](Clingo::Symbol atom) -> Puzzle::Fact::Ptr {
        if (atom.type() == Clingo::SymbolType::Function) {
            // TODO: Parser specific exception handler? Otherwise get weird catches on the grounding handler
            if (string("cycle") == atom.name()) {
                auto args = atom.arguments();
                auto result = make_shared<Puzzle::CycleEdge>(args[0].number(), args[1].number());
                return dynamic_pointer_cast<Puzzle::Fact>(result);
            } else if (string("total_cost") == atom.name()) {

                auto args = atom.arguments();
                auto result = make_shared<Puzzle::Fact1<uint32_t>>(atom.name(), args[0].number());
                return dynamic_pointer_cast<Puzzle::Fact>(result);

            }
            return Puzzle::Fact::Ptr();
        }
    };

    fact_handler = [](Puzzle::Fact::Ptr fact) -> string {
        return "";
    };

    initializeUI();
    interface.addSeparator("Domain");
}

void TSPDemo::mouseDown(MouseEvent event) {
    bool near_existing = false;
    ivec2 existing;
    for (const auto &center: circle_centers) {
        glm::dvec2 diff = center - event.getPos();
        double distance = glm::length(diff);
        if (distance < 5.0) {
            near_existing = true;
            existing = center;
            break;
        }
    }
    if (!near_existing) {
        circle_centers.emplace_back(event.getX(), event.getY());
        domain_dirty = true;
    }

}


void TSPDemo::draw() {
    auto tsp_renderer = (Puzzle::TSPRenderer *) renderer;
    auto tsp_domain = (Puzzle::TSPDomain *) domain;
    if (domain_dirty) {
        tsp_renderer->set_nodes(circle_centers);
        tsp_domain->points = circle_centers;
        Puzzle::Puzzle puzzle;
        puzzle.compose(*domain);
        Puzzle::ASPSolver solver(solution_span);
        solver.configure_custom_fact_handler(fact_handler);
        solver.configure_parser(parser);
        solutions = solver.solve(puzzle);
        setUILimits(solutions.size() - 1);

        if (solutions.empty()) {
            //cerr << puzzle.to_string() << endl;
            cerr << "No solutions found" << endl;

        }
        domain_dirty = false;
        screen_dirty = true;
    }
    if (screen_dirty) {
        if (solution_index < solutions.size()) {
            renderer->render(solutions.at(solution_index));
        }
        screen_dirty = false;
    }
    if (!hide_ui) {
        interface.draw();
    } else {
        screen_dirty = true;
        hide_ui = false;
    }
}

CINDER_APP(TSPDemo, RendererGl(RendererGl::Options().msaa(4)))