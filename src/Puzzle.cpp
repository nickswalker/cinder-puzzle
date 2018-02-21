#include "puzzle/Puzzle.h"

using namespace std;
namespace Puzzle {
    Puzzle::Puzzle::Puzzle() = default;

    void Puzzle::Puzzle::compose(const Fact::Ptr &fact) {
        facts.push_back(fact);

    }

    void Puzzle::compose(const Rule &fact) {

    }

    void Puzzle::compose(const Domain &domain) {
        auto new_facts = domain.get_facts();
        facts.insert(facts.end(), new_facts.begin(), new_facts.end());
    }

    vector<Fact::Ptr> Puzzle::get_facts() const {
        return facts;
    }

    string Puzzle::to_string() const {
        std::string ret;
        for (int i = 0; i < facts.size(); ++i) {
            ret += facts.at(i)->to_string();
            ret += "\n";
        }
        return ret;
    }
}
