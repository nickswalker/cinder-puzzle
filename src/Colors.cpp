#include "puzzle_demos/Colors.h"

using namespace std;
using namespace ci;
namespace PuzzleDemos {
    namespace Color {

        map<string, ci::Color> get_solarized() {
            map<string, ci::Color> map;
            map.emplace(string("base0"), ci::Color(.39, .48, .51));
            map.emplace(string("base01"), ci::Color(.34, .43, .45));
            map.emplace(string("base03"), ci::Color(.00, .16, .21));
            map.emplace(string("base02"), ci::Color(.02, .21, .26));
            map.emplace(string("blue"), ci::Color(.14, .54, .82));
            map.emplace(string("green"), ci::Color(.52, .60, .00));
            map.emplace(string("cyan"), ci::Color(.16, .63, .59));
            map.emplace(string("orange"), ci::Color(.79, .29, .08));
            return map;
        }

        map<string, ci::Color> get_solarized_subset(const char **names) {

        };
    }
}