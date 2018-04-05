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

using namespace ci;
using namespace ci::app;
using namespace std;


class TSPDemo : public App {
public:
    Puzzle::TSPRenderer *renderer;
    Puzzle::TSPDomain *domain;
    function<Puzzle::Fact::Ptr(Clingo::Symbol)> parser;
    function<string(Puzzle::Fact::Ptr)> fact_handler;
    vector<vector<Puzzle::Fact::Ptr> > solutions;
    uint32_t solution_index = 0;
    uint32_t solution_span = 100;
    int last_x = 0;
    int last_y = 0;
    bool screen_dirty = true;
    bool domain_dirty = true;

    vector<ivec2> circle_centers;

    void setup() override;

    void resize() override;

    void mouseDown(MouseEvent event) override;

    void mouseDrag(MouseEvent event) override;

    void mouseUp(MouseEvent event) override;

    void keyDown(KeyEvent event) override;

    void keyUp(KeyEvent event) override;

    void draw() override;

};

void TSPDemo::setup() {
    gl::enableDepthRead();
    gl::enableDepthWrite();

    vector<string> color_strings;
    renderer = new Puzzle::TSPRenderer();
    domain = new Puzzle::TSPDomain();

    parser = [](Clingo::Symbol atom) -> Puzzle::Fact::Ptr {
        cout << atom << endl;
        if (atom.type() == Clingo::SymbolType::Function) {
            // TODO: Parser specific exception handler? Otherwise get weird catches on the grounding handler
            if (string("cycle") == atom.name()) {
                auto args = atom.arguments();
                auto result = make_shared<Puzzle::CycleEdge>(args[0].number(), args[1].number());
                return dynamic_pointer_cast<Puzzle::Fact>(result);
            }
            return Puzzle::Fact::Ptr();
        }
    };

    fact_handler = [](Puzzle::Fact::Ptr fact) -> string {
        return "";
    };
}

void TSPDemo::resize() {
    screen_dirty = true;
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

void TSPDemo::mouseDrag(MouseEvent event) {

}

void TSPDemo::draw() {
    if (domain_dirty) {
        renderer->set_nodes(circle_centers);
        domain->points = circle_centers;
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
        if (solutions.size() != 0) {
            renderer->render(solutions.at(solution_index));
        }
        screen_dirty = false;
    }
}

void TSPDemo::mouseUp(MouseEvent event) {
    AppBase::mouseUp(event);
}

void TSPDemo::keyDown(KeyEvent event) {
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

void TSPDemo::keyUp(KeyEvent event) {
    AppBase::keyUp(event);
}

CINDER_APP(TSPDemo, RendererGl)