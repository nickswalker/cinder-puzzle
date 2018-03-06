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

using namespace ci;
using namespace ci::app;
using namespace std;


class PixelsDemo : public App {
public:
    Puzzle::PixelsRenderer *renderer;
    Puzzle::PixelsDomain *domain;
    function<Puzzle::Fact::Ptr(Clingo::Symbol)> parser;
    function<string(Puzzle::Fact::Ptr)> fact_handler;
    vector<vector<Puzzle::Fact::Ptr> > solutions;
    uint32_t solution_index = 0;
    uint32_t solution_span = 100;
    int last_x = 0;
    int last_y = 0;
    bool screen_dirty = true;
    bool domain_dirty = true;

    void setup() override;

    void resize() override;

    void mouseDown(MouseEvent event) override;

    void mouseDrag(MouseEvent event) override;

    void mouseUp(MouseEvent event) override;

    void keyDown(KeyEvent event) override;

    void keyUp(KeyEvent event) override;

    void draw() override;

};

void PixelsDemo::setup() {
    gl::enableDepthRead();
    gl::enableDepthWrite();

    map<string, Color> color_map;
    //color_map.insert(pair<string, Color>(string("base0"), Color(.39, .48, .51)));
    //color_map.insert(pair<string, Color>(string("base01"), Color(.34, .43, .45)));
    //color_map.insert(pair<string, Color>(string("base03"), Color(.00, .16, .21)));
    color_map.insert(pair<string, Color>(string("base02"), Color(.02, .21, .26)));
    color_map.insert(pair<string, Color>(string("blue"), Color(.14, .54, .82)));
    color_map.insert(pair<string, Color>(string("green"), Color(.52, .60, .00)));
    color_map.insert(pair<string, Color>(string("cyan"), Color(.16, .63, .59)));
    color_map.insert(pair<string, Color>(string("orange"), Color(.79, .29, .08)));

    vector<string> color_strings;
    for (auto &pair: color_map) {
        color_strings.emplace_back(pair.first);
    }
    renderer = new Puzzle::PixelsRenderer(color_map);
    renderer->scale = 16;
    domain = new Puzzle::PixelsDomain(40, 30, color_strings);
    domain->neighbors_different = true;

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
}

void PixelsDemo::resize() {
    screen_dirty = true;
}

void PixelsDemo::mouseDown(MouseEvent event) {
    int x = event.getPos().x;
    int y = event.getPos().y;
    int grid_x = x / renderer->scale;
    int grid_y = y / renderer->scale;
    domain->increment_constraint(grid_x, grid_y);
    domain_dirty = true;

    last_x = grid_x;
    last_y = grid_y;

}

void PixelsDemo::mouseDrag(MouseEvent event) {

}

void PixelsDemo::draw() {
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
            domain->clear_constraint(last_x, last_y);
            return;

        }
        domain_dirty = false;
        screen_dirty = true;
    }
    if (screen_dirty) {
        renderer->render(solutions.at(solution_index));
        screen_dirty = false;
    }
}

void PixelsDemo::mouseUp(MouseEvent event) {
    AppBase::mouseUp(event);
}

void PixelsDemo::keyDown(KeyEvent event) {
    AppBase::keyDown(event);
    switch (event.getCode()) {
        case KeyEvent::KEY_UP: {
            solution_index += 1;
            solution_index %= solution_span;
            screen_dirty = true;
            break;
        }
        case KeyEvent::KEY_DOWN: {
            solution_index -= 1;
            solution_index %= solution_span;
            screen_dirty = true;
            break;
        }
        case KeyEvent::KEY_s: {
            writeImage(to_string(solution_index) + ".png", copyWindowSurface());
            break;
        }
        default:
            break;
    }

}

void PixelsDemo::keyUp(KeyEvent event) {
    AppBase::keyUp(event);
}

CINDER_APP(PixelsDemo, RendererGl)