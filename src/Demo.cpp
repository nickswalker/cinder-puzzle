#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Arcball.h"
#include "cinder/Sphere.h"
#include <clingo.hh>
#include <iostream>
#include <puzzle/ASPSolver.h>
#include <puzzle/PixelsDomain.h>
#include <puzzle/Puzzle.h>

#include "puzzle/Resources.h"

using namespace ci;
using namespace ci::app;


class Demo : public App {
public:
    void setup() override;
    void resize() override;
    void mouseDown( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;
    void draw() override;

};

void Demo::setup() {
    gl::enableDepthRead();
    gl::enableDepthWrite();

    Puzzle::PixelsDomain domain(100, 100);
    Puzzle::Puzzle puzzle;
    puzzle.compose(domain);
    Puzzle::ASPSolver solver;
    solver.solve(puzzle);

}

void Demo::resize()
{
}

void Demo::mouseDown(MouseEvent event) {

}

void Demo::mouseDrag(MouseEvent event) {

}

void Demo::draw() {
    gl::clear(Color(0, 0.0f, 0.0f));

    gl::drawSolidRect(cinder::Rectf(10., 10., 10., 10.));
    gl::drawSolidCircle(getWindowCenter(), 200);
}

CINDER_APP(Demo, RendererGl)