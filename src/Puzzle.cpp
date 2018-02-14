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
}
