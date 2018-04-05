#include "puzzle/ASPSolver.h"
#include <puzzle/RawFact.h>
#include <puzzle/PixelColor.h>
#include <puzzle/Constant.h>
#include <clingo.hh>
#include <functional>

using namespace Clingo;
using namespace std;
namespace Puzzle {

    struct ConfigurableSolveEventHandler : public SolveEventHandler {

        std::function<bool(Model const &model)> on_model_handler;
        std::function<void(SolveResult)> on_finish_handler;

        ConfigurableSolveEventHandler(std::function<bool(Model const &model)> on_model,
                                      std::function<void(SolveResult)> on_finish) : on_model_handler(on_model),
                                                                                    on_finish_handler(on_finish) {
        }

        bool on_model(Model const &model) override {
            return SolveEventHandler::on_model(model);
        }

        virtual void on_finish(SolveResult result) {
            SolveEventHandler::on_finish(result);
        }
    };

    void ASPSolver::add(const string &fragment) {
        control.add("base", {}, fragment.c_str());
    }

    void ASPSolver::solve(const Puzzle &puzzle, function<void(vector<Fact::Ptr>)> callback) {
        vector<Fact::Ptr> facts = puzzle.get_facts();
        control.interrupt();
        for (auto &fact : facts) {
            if (auto raw_fact = dynamic_pointer_cast<RawFact>(fact)) {
                control.add("base", {}, raw_fact->fact.c_str());
                continue;
            } else if (auto constant = dynamic_pointer_cast<Constant>(fact)) {
                ostringstream out;
                out << "#const " << constant->name << "=" << constant->value << ".";
                control.add("base", {}, out.str().c_str());
            } else if (custom_fact_handler) {
                auto result = custom_fact_handler(fact);
                if (result.empty()) {
                    cerr << "Couldn't handle fact: " << fact << endl;
                    continue;
                }
                control.add("base", {}, result.c_str());
            } else {
                cerr << "Couldn't handle fact: " << fact << endl;
                continue;
            }
        }
        vector<vector<Fact::Ptr>> solution;

        try {
            control.ground({{"base", {}}});
        }
        catch (exception const &e) {
            cerr << "Grounding failed with: " << e.what() << endl;
        }
        ConfigurableSolveEventHandler *handler = new ConfigurableSolveEventHandler(
                [this, callback](Model const &m) -> bool {
                    vector<Fact::Ptr> model_facts;
                    for (auto &atom : m.symbols(Clingo::ShowType::Shown)) {

                        auto result = this->parser(atom);
                        if (!result) {
                            continue;
                        }
                        model_facts.push_back(result);
                    }
                    std::sort(model_facts.begin(), model_facts.end());
                    callback(model_facts);
                    return true;
                }, [](SolveResult result) {
                    cout << "RESULT" << endl;
                    cout << result << endl;
                });
        auto handle = control.solve({}, handler, true);

    }

    vector<vector<Fact::Ptr>> ASPSolver::solve(const Puzzle &puzzle) {

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