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
#include <puzzle/TilingRenderer.h>
#include <puzzle/TilingDomain.h>
#include <puzzle/CycleEdge.h>
#include <puzzle/FactN.h>
#include <puzzle_demos/Colors.h>
#include <puzzle_demos/PuzzleDemoApp.h>

using namespace ci;
using namespace ci::app;
using namespace std;


class TilingDemo : public PuzzleDemos::PuzzleDemoApp {
public:
    int last_x = 0;
    int last_y = 0;

    vector<ivec2> circle_centers;

    void setup() override;

    void draw() override;

};

void TilingDemo::setup() {
    PuzzleDemos::PuzzleDemoApp::setup();

    vector<string> color_strings;
    renderer = new Puzzle::TilingRenderer(PuzzleDemos::Color::get_solarized());
    renderer->scale = 4;
    domain = new Puzzle::TilingDomain(20, 20);
    auto tiling_domain = (Puzzle::TilingDomain *) domain;
    auto tiling_renderer = (Puzzle::TilingRenderer *) renderer;

    parser = [](Clingo::Symbol atom) -> Puzzle::Fact::Ptr {
        if (atom.type() == Clingo::SymbolType::Function) {
            // TODO: Parser specific exception handler? Otherwise get weird catches on the grounding handler
            if (string("covered") == atom.name()) {
                auto args = atom.arguments();
                auto result = make_shared<Puzzle::Fact3<uint32_t, uint32_t, uint32_t>>(string("covered"),
                                                                                       args[0].number(),
                                                                                       args[1].number(),
                                                                                       args[2].number());
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
    interface.addParam<int>("Num Points",
                            [this, tiling_domain](int new_val) {
                                tiling_domain->set_canvas_size(new_val, new_val);
                                tiling_renderer->set_canvas_size(new_val, new_val);
                                domain_dirty = true;
                                screen_dirty = true;
                            },
                            [this, tiling_domain]() -> int { return tiling_domain->get_canvas_size().x; });
    interface.setOptions("Num Pixels", "min=1 max=64 step=1");
}


void TilingDemo::draw() {
    if (domain_dirty) {
        Puzzle::Puzzle puzzle;
        puzzle.compose(*domain);
        Puzzle::ASPSolver solver(solution_span);
        solver.configure_custom_fact_handler(fact_handler);
        solver.configure_parser(parser);
        solutions = solver.solve(puzzle);

        if (solutions.empty()) {
            cerr << puzzle.to_string() << endl;
            cerr << "No solutions found, removing last constraint" << endl;

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


CINDER_APP(TilingDemo, RendererGl(RendererGl::Options().msaa(4)))