#include <puzzle/Constant.h>
#include <sstream>

using namespace std;

namespace Puzzle {
    Constant::Constant(string name, string value) : name(name), value(value) {};

    Constant::Constant(string name, int value) : name(name), value(std::to_string(value)) {};

    string Constant::to_string() {
        ostringstream out;
        out << name << "=" << value << ".";
        return out.str();
    }
}