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

using namespace ci;
using namespace ci::app;
using namespace std;


class ShapesDemo : public App {
public:
    Puzzle::ShapesRenderer *renderer;
    Puzzle::ShapesDomain *domain;
    vector<vector<Puzzle::Fact::Ptr> > solutions;
    function<Puzzle::Fact::Ptr(Clingo::Symbol)> parser;
    function<string(Puzzle::Fact::Ptr)> fact_handler;
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

void ShapesDemo::setup() {
    gl::enableDepthRead();
    gl::enableDepthWrite();

    renderer = new Puzzle::ShapesRenderer();

    parser = [](Clingo::Symbol atom) -> Puzzle::Fact::Ptr {
        if (atom.type() == Clingo::SymbolType::Function) {
            if (string("rect") == atom.name()) {
                auto args = atom.arguments();
                auto result = make_shared<Puzzle::Rect>(args[0].number(), args[1].number(), args[2].number(),
                                                        args[3].number());
                return dynamic_pointer_cast<Puzzle::Fact>(result);
            }
            return Puzzle::Fact::Ptr();
        }
    };
    renderer->scale = 16;
    domain = new Puzzle::ShapesDomain(2, 2);
}

void ShapesDemo::resize() {
    screen_dirty = true;
}

void ShapesDemo::mouseDown(MouseEvent event) {
    int x = event.getPos().x;
    int y = event.getPos().y;
    int grid_x = x / renderer->scale;
    int grid_y = y / renderer->scale;

    //TODO: Poke the domain somehow

    last_x = grid_x;
    last_y = grid_y;

}

void ShapesDemo::mouseDrag(MouseEvent event) {

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
        if (!solutions.empty()) {
            renderer->render(solutions.at(solution_index));
        }
        screen_dirty = false;
    }
}

void ShapesDemo::mouseUp(MouseEvent event) {
    AppBase::mouseUp(event);
}

void ShapesDemo::keyDown(KeyEvent event) {
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

void ShapesDemo::keyUp(KeyEvent event) {
    AppBase::keyUp(event);
}

CINDER_APP(ShapesDemo, RendererGl)