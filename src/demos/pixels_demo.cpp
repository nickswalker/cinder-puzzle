#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <cinder/params/Params.h>
#include <puzzle/ASPSolver.h>
#include <puzzle/PixelsDomain.h>
#include <puzzle/Puzzle.h>
#include <puzzle/PixelsRenderer.h>
#include <puzzle/PixelColor.h>
#include <map>
#include <functional>
#include <puzzle_demos/PuzzleDemoApp.h>

using namespace ci;
using namespace ci::app;
using namespace std;


class PixelsDemo : public PuzzleDemos::PuzzleDemoApp {
public:

    int last_x = 0;
    int last_y = 0;

    void setup() override;

    void mouseDown(MouseEvent event) override;

    void draw() override;
};

void PixelsDemo::setup() {
    PuzzleDemos::PuzzleDemoApp::setup();

    map<string, Color> color_map;
    //color_map.insert(pair<string, Color>(string("base0"), Color(.39, .48, .51)));
    //color_map.insert(pair<string, Color>(string("base01"), Color(.34, .43, .45)));
    //color_map.insert(pair<string, Color>(string("base03"), Color(.00, .16, .21)));
    color_map.emplace(string("base02"), Color(.02, .21, .26));
    color_map.emplace(string("blue"), Color(.14, .54, .82));
    color_map.emplace(string("green"), Color(.52, .60, .00));
    color_map.emplace(string("cyan"), Color(.16, .63, .59));
    color_map.emplace(string("orange"), Color(.79, .29, .08));

    vector<string> color_strings;
    for (auto &pair: color_map) {
        color_strings.emplace_back(pair.first);
    }
    renderer = new Puzzle::PixelsRenderer(color_map);
    renderer->scale = 64;
    auto pixels_renderer = (Puzzle::PixelsRenderer *) renderer;

    pixels_renderer->set_canvas_size(10, 10);
    domain = new Puzzle::PixelsDomain(10, 10, color_strings);
    auto pixels_domain = (Puzzle::PixelsDomain *) domain;
    pixels_domain->neighbors_different = true;

    parser = [](Clingo::Symbol atom) -> Puzzle::Fact::Ptr {
        //cout << atom << endl;
        if (atom.type() == Clingo::SymbolType::Function) {
            if (string("cpix") == atom.name()) {
                auto args = atom.arguments();
                auto result = make_shared<Puzzle::PixelColor>(args[1].number(), args[2].number(), args[0].name());
                return dynamic_pointer_cast<Puzzle::Fact>(result);
            }
            return Puzzle::Fact::Ptr();
        }
    };

    fact_handler = [](Puzzle::Fact::Ptr fact) -> string {
        if (auto pixel = dynamic_pointer_cast<Puzzle::PixelColor>(fact)) {
            ostringstream out;
            out << "cpix(" << pixel->color << "," << pixel->x << "," << pixel->y << ").";
            return out.str();
        } else {
            return "";
        }
    };

    initializeUI();
    interface.addSeparator("Domain");
    interface.addParam<int>("Num Pixels",
                            [this, pixels_domain, pixels_renderer](int new_val) {
                                pixels_domain->set_canvas_size(new_val, new_val);
                                pixels_renderer->set_canvas_size(new_val, new_val);
                                domain_dirty = true;
                                screen_dirty = true;
                            },
                            [this, pixels_domain]() -> int { return pixels_domain->get_canvas_size().x; });
    interface.setOptions("Num Pixels", "min=1 max=64 step=1");


}

void PixelsDemo::mouseDown(MouseEvent event) {
    int x = event.getPos().x;
    int y = event.getPos().y;
    int grid_x = x / renderer->scale;
    int grid_y = y / renderer->scale;
    auto pixels_domain = (Puzzle::PixelsDomain *) domain;
    pixels_domain->increment_constraint(grid_x, grid_y);
    domain_dirty = true;

    last_x = grid_x;
    last_y = grid_y;

}

void PixelsDemo::draw() {
    auto pixels_domain = (Puzzle::PixelsDomain *) domain;
    auto pixels_renderer = (Puzzle::PixelsRenderer *) renderer;
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
            pixels_domain->clear_constraint(last_x, last_y);
            return;
        }
        domain_dirty = false;
        screen_dirty = true;
    }
    if (screen_dirty) {
        pixels_renderer->set_constraint_map(pixels_domain->constraints);
        pixels_renderer->show_constraints = !hide_ui;
        renderer->render(solutions.at(solution_index));
        screen_dirty = false;
    }
    if (!hide_ui) {
        interface.draw();
    }
}


CINDER_APP(PixelsDemo, ci::app::RendererGl)