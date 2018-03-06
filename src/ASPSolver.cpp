#include "puzzle/ASPSolver.h"
#include <puzzle/RawFact.h>
#include <puzzle/PixelColor.h>
#include <puzzle/Constant.h>
#include <clingo.hh>

using namespace Clingo;
using namespace std;
namespace Puzzle {

    void ASPSolver::add(const string &fragment) {
        control.add("base", {}, fragment.c_str());
    }

    vector<vector<Fact::Ptr>> ASPSolver::solve(const Puzzle &puzzle) {
        vector<Fact::Ptr> facts = puzzle.get_facts();
        for (auto &fact : facts) {
            if (auto raw_fact = dynamic_pointer_cast<RawFact>(fact)) {
                control.add("base", {}, raw_fact->fact.c_str());
                continue;
            } else if (auto constant = dynamic_pointer_cast<Constant>(fact)) {
                ostringstream out;
                out << "#const " << constant->name << "=" << constant->value << ".";
                control.add("base", {}, out.str().c_str());
            } else {
                auto result = custom_fact_handler(fact);
                if (result.empty()) {
                    cerr << "Couldn't handle fact: " << fact << endl;
                    continue;
                }
                control.add("base", {}, result.c_str());
            }
        }
        vector<vector<Fact::Ptr>> solution;

        try {

            control.ground({{"base", {}}});
            auto handle = control.solve();
            for (auto m : handle) {
                vector<Fact::Ptr> model_facts;
                for (auto &atom : m.symbols(Clingo::ShowType::Shown)) {
                    auto result = (this->parser)(atom);
                    if (!result) {
                        continue;
                    }
                    model_facts.push_back(result);
                }
                std::sort(model_facts.begin(), model_facts.end());
                solution.push_back(model_facts);
            }
            cout << handle.get() << endl;
        }
        catch (exception const &e) {
            cerr << "example failed with: " << e.what() << endl;
        }
        return solution;
    }

    ASPSolver::ASPSolver(uint32_t max_solutions = 1) {
        logger = [](Clingo::WarningCode, char const *message) {
            cerr << message << endl;
        };
        control = Control({to_string(max_solutions).c_str()}, logger, 20);
    }

    void ASPSolver::load(const string &path) {
        control.load(path.c_str());
    }

    void ASPSolver::configure_parser(std::function<Fact::Ptr(Clingo::Symbol)> &parser) {
        this->parser = parser;
    }

    void ASPSolver::configure_custom_fact_handler(std::function<string(Fact::Ptr)> &parser) {
        this->custom_fact_handler = parser;
    }
}