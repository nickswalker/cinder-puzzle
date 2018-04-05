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
        std::function<Fact::Ptr(Clingo::Symbol & )> parser;
        std::function<std::string(Fact::Ptr)> custom_fact_handler;
    public:


        explicit ASPSolver(uint32_t max_solutions);

        void add(const std::string &fragment);

        void load(const std::string &path);

        void configure_parser(std::function<Fact::Ptr(Clingo::Symbol)> &parser);

        // Synchronous
        std::vector<std::vector<Fact::Ptr>> solve(const Puzzle &puzzle) override;

        void solve(const Puzzle &puzzle, std::function<void(std::vector<Fact::Ptr>)> callback);

        void configure_custom_fact_handler(std::function<std::string(Fact::Ptr)> &parser);

    };

}

#endif //PUZZLE_ASPSOLVER_H
