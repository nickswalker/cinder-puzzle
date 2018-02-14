#include "puzzle/ASPSolver.h"

#include <clingo.hh>
#include <puzzle/Puzzle.h>
#include <puzzle/RawFact.h>

using namespace Clingo;
using namespace std;
namespace Puzzle {

    void ASPSolver::add(const string &fragment) {
        control.add("base", {}, fragment.c_str());
    }

    vector<Fact::Ptr> ASPSolver::solve(const Puzzle &puzzle) {
        vector<Fact::Ptr> facts = puzzle.get_facts();
        for (auto &fact : facts) {

            if (auto raw_fact = dynamic_pointer_cast<RawFact>(fact)) {
                control.add("base", {}, raw_fact->fact.c_str());
                continue;
            }

        }
        try {
            control.ground({{"base", {}}});
            for (auto m : control.solve()) {
                for (auto &atom : m.symbols()) {
                    auto test = atom.type();
                    auto blah = atom.arguments();
                    auto hah = atom.name();
                    cout << " " << atom;
                }
                cout << "\n";
            }
        }
        catch (exception const &e) {
            cerr << "example failed with: " << e.what() << endl;
        }
    }

    ASPSolver::ASPSolver() {
        logger = [](Clingo::WarningCode, char const *message) {
            cerr << message << endl;
        };
        control = Control({}, logger, 20);
    }

    void ASPSolver::load(const string &path) {
        control.load(path.c_str());
    }
}