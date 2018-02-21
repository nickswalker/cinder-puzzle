#include "puzzle/ASPSolver.h"

#include <clingo.hh>
#include <puzzle/Puzzle.h>
#include <puzzle/RawFact.h>
#include <puzzle/PixelColor.h>

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
            }

        }
        vector<vector<Fact::Ptr>> solution;

        try {
            control.ground({{"base", {}}});
            auto handle = control.solve();
            for (auto m : handle) {
                vector<Fact::Ptr> model_facts;
                for (auto &atom : m.symbols(Clingo::ShowType::Shown)) {
                    if (atom.type() == Clingo::SymbolType::Function) {
                        if (string("cpix") == atom.name()) {
                            auto args = atom.arguments();
                            model_facts.push_back(
                                    make_shared<PixelColor>(args[1].number(), args[2].number(), args[0].name()));
                        }
                    }
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
}