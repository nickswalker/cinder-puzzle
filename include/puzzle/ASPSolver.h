#ifndef PUZZLE_ASPSOLVER_H
#define PUZZLE_ASPSOLVER_H

#include <clingo.hh>
#include <puzzle/Solver.h>
#include <functional>
#include "Puzzle.h"

namespace Puzzle {

    class ASPSolver : public Solver {
    protected:
        Clingo::Logger logger;
        Clingo::Control control;
    public:
        std::function<Fact::Ptr(Clingo::Symbol & )> parser;

        explicit ASPSolver(uint32_t max_solutions);

        void add(const std::string &fragment);

        void load(const std::string &path);

        void configure_parser(std::function<Fact::Ptr(Clingo::Symbol)> &parser);

        std::vector<std::vector<Fact::Ptr>> solve(const Puzzle &puzzle) override;

    };

}

#endif //PUZZLE_ASPSOLVER_H
