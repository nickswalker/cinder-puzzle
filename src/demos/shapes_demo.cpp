#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <puzzle/ASPSolver.h>
#include <puzzle/PixelsDomain.h>
#include <puzzle/Puzzle.h>
#include <puzzle/PixelsRenderer.h>
#include <map>
#include <puzzle/Rect.h>
#include <functional>
#include <puzzle/ShapesRenderer.h>
#include <puzzle/ShapesDomain.h>
#include <puzzle_demos/Colors.h>
#include <puzzle_demos/PuzzleDemoApp.h>

using namespace ci;
using namespace ci::app;
using namespace std;


class ShapesDemo : public PuzzleDemos::PuzzleDemoApp {
public:
    size_t num_shapes = 2;

    void setup() override;

    void draw() override;

};

void ShapesDemo::setup() {
    PuzzleDemos::PuzzleDemoApp::setup();

    renderer = new Puzzle::ShapesRenderer(PuzzleDemos::Color::get_solarized());
    renderer->scale = 64;
    parser = [](Clingo::Symbol atom) -> Puzzle::Fact::Ptr {
        //cout << atom.to_string() << endl;
        if (atom.type() == Clingo::SymbolType::Function) {
            if (string("rect") == atom.name()) {
                auto args = atom.arguments();
                auto result = make_shared<Puzzle::Rect>(args[0].number(), args[1].number(), args[2].number(),
                                                        args[3].number());
                auto test = args[4].arguments();
                return dynamic_pointer_cast<Puzzle::Fact>(result);
            }
            return Puzzle::Fact::Ptr();
        }
    };
    domain = new Puzzle::ShapesDomain(3, 3);
    auto shapes_domain = (Puzzle::ShapesDomain *) domain;
    shapes_domain->set_num_shapes(num_shapes);

    auto shapes_renderer = (Puzzle::ShapesRenderer *) renderer;
    shapes_renderer->set_canvas_size(3, 3);
    initializeUI(1000);

    interface.addSeparator("Domain");
    interface.addParam<int>("Num Points",
                            [this, shapes_domain, shapes_renderer](int new_val) {
                                shapes_domain->set_canvas_size(new_val, new_val);
                                shapes_renderer->set_canvas_size(new_val, new_val);
                                domain_dirty = true;
                                screen_dirty = true;
                            },
                            [this, shapes_domain]() -> int { return shapes_domain->get_canvas_size().x; });
    interface.setOptions("Num Points", "min=2 max=8 step=1");

    interface.addParam<int>("Num Shapes",
                            [this, shapes_domain](int new_val) {
                                shapes_domain->set_num_shapes(new_val);
                                domain_dirty = true;
                                screen_dirty = true;
                            },
                            [this, shapes_domain]() -> int { return shapes_domain->num_shapes; });
    interface.setOptions("Num Shapes", "min=2 max=8 step=1");
}


void ShapesDemo::draw() {
    if (domain_dirty) {
        Puzzle::Puzzle puzzle;
        puzzle.compose(*domain);
        Puzzle::ASPSolver solver(solution_span);
        solver.configure_parser(parser);
        solver.configure_custom_fact_handler(fact_handler);
        solutions = solver.solve(puzzle);

        if (solutions.empty()) {
            cerr << puzzle.to_string() << endl;
            cerr << "No solutions found, removing last constraint" << endl;
            // TODO: Back out somehow
            //return;
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

CINDER_APP(ShapesDemo, RendererGl)