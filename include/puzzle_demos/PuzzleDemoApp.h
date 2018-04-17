#ifndef PUZZLE_PUZZLEDEMOAPP_H
#define PUZZLE_PUZZLEDEMOAPP_H

#include <cinder/Cinder.h>
#include <cinder/app/App.h>
#include <cinder/params/Params.h>
#include <clingo.hh>
#include <cinder/ImageIo.h>
#include <puzzle/Fact.h>

#include <puzzle/Renderer.h>
#include <puzzle/Domain.h>

namespace PuzzleDemos {
    class PuzzleDemoApp : public ci::app::App {
    protected:
        ci::params::InterfaceGl interface;
        std::function<Puzzle::Fact::Ptr(Clingo::Symbol)> parser;
        std::function<std::string(Puzzle::Fact::Ptr)> fact_handler;
        std::vector<std::vector<Puzzle::Fact::Ptr> > solutions;
        uint32_t solution_index;
        uint32_t solution_span;

        bool screen_dirty;
        bool domain_dirty;
        bool hide_ui;

        Puzzle::Renderer *renderer;
        Puzzle::Domain *domain;

        void resize();

        void save();

        void prepareSettings(Settings *settings);

        virtual void draw() = 0;

        void setup();

        void initializeUI(int max_num_solutions = 100);

        void keyDown(ci::app::KeyEvent event);

        void setUILimits(int max_solution_index);
    };


}

#endif //PUZZLE_PUZZLEDEMOAPP_H
