#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <puzzle/ASPSolver.h>
#include <puzzle/PixelsDomain.h>
#include <puzzle/Puzzle.h>
#include <puzzle/PixelsRenderer.h>
#include <map>

using namespace ci;
using namespace ci::app;
using namespace std;


class Demo : public App {
public:
    Puzzle::PixelsRenderer *renderer;
    vector<vector<Puzzle::Fact::Ptr> > solutions;
    uint32_t solution_index = 0;
    void setup() override;
    void resize() override;
    void mouseDown( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;
    void draw() override;

};

void Demo::setup() {
    gl::enableDepthRead();
    gl::enableDepthWrite();

    map<string, Color> color_map;
    color_map.insert(pair<string, Color>(string("r"), Color(1, 0, 0)));
    color_map.insert(pair<string, Color>(string("g"), Color(0, 1, 0)));
    color_map.insert(pair<string, Color>(string("b"), Color(0, 0, 1)));
    color_map.insert(pair<string, Color>(string("y"), Color(1, 1, 0)));
    renderer = new Puzzle::PixelsRenderer(color_map);
    renderer->scale = 16;
    Puzzle::PixelsDomain domain(40, 30);
    domain.neighbors_different = true;
    Puzzle::Puzzle puzzle;
    puzzle.compose(domain);
    Puzzle::ASPSolver solver(255);
    solutions = solver.solve(puzzle);
    if (solutions.empty()) {
        cerr << "No solutions found" << endl;
        cerr << puzzle.to_string() << endl;
        exit(1);
    }
}

void Demo::resize() {
}

void Demo::mouseDown(MouseEvent event) {
    solution_index += 1;
    writeImage(to_string(solution_index) + ".png", copyWindowSurface());
}

void Demo::mouseDrag(MouseEvent event) {

}

void Demo::draw() {
    renderer->render(solutions.at(solution_index));
}

CINDER_APP(Demo, RendererGl)