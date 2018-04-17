#include <puzzle_demos/PuzzleDemoApp.h>
#include <cinder/gl/gl.h>
#include <cinder/Cinder.h>

namespace PuzzleDemos {
    void PuzzleDemoApp::resize() {
        screen_dirty = true;
    }

    void PuzzleDemoApp::setup() {
        ci::gl::enableDepthRead();
        ci::gl::enableDepthWrite();
        domain_dirty = true;
        screen_dirty = true;
        solution_span = 10;
        solution_index = 0;

    }

    void PuzzleDemoApp::initializeUI(int max_num_solutions) {
        interface = ci::params::InterfaceGl("Params", {200, 400});
        interface.addSeparator("Solver");
        interface.addParam<int>("Solution Index",
                                [this](int new_val) {
                                    solution_index = new_val;
                                    screen_dirty = true;
                                },
                                [this]() -> int { return (int) solution_index; });
        {
            std::ostringstream stream;
            stream << "min=0 max=" << solution_span - 1 << " step=1";
            interface.setOptions("Solution Index", stream.str());
        }
        interface.addParam<int>("Num Solutions",
                                [this](int new_val) {
                                    solution_span = new_val;
                                    std::ostringstream stream;
                                    stream << "min=0 max=" << solution_span - 1 << " step=1 keyIncr=up keyDecr=down";
                                    interface.setOptions("Solution Index", stream.str());
                                    screen_dirty = true;
                                    domain_dirty = true;
                                },
                                [this]() -> int { return (int) solution_span; });
        {
            std::ostringstream stream;
            stream << "min=0 max=" << max_num_solutions << "step=1 keyIncr=UP keyDecr=DOWN";
            interface.setOptions("Num Solutions", stream.str());
        }

        interface.addSeparator("UI");
        interface.addParam<int>("Scale",
                                [this](int new_val) {
                                    renderer->scale = new_val;
                                    screen_dirty = true;
                                },
                                [this]() -> int { return (int) renderer->scale; });
        interface.setOptions("Scale", "min=1 max=128 step=1 keyIncr=q keyDecr=a");

        interface.addButton("Save", std::bind(&PuzzleDemoApp::save, this));
    }

    void PuzzleDemoApp::setUILimits(int max_solution_index) {
        {
            std::ostringstream stream;
            stream << "min=0 max=" << max_solution_index << " step=1";
            interface.setOptions("Solution Index", stream.str());
        }
    }

    void PuzzleDemoApp::prepareSettings(cinder::app::AppBase::Settings *settings) {
        settings->setHighDensityDisplayEnabled(true);
    }

    void PuzzleDemoApp::save() {
        hide_ui = true;
        draw();
        ci::writeImage(std::to_string(solution_index) + ".png", copyWindowSurface());
        hide_ui = false;
        draw();
    }

    void PuzzleDemoApp::keyDown(ci::app::KeyEvent event) {
        ci::app::App::keyDown(event);
        switch (event.getCode()) {
            case ci::app::KeyEvent::KEY_h: {
                hide_ui = !hide_ui;
                screen_dirty = true;
                break;
            }
            default:
                break;
        }
    }
}