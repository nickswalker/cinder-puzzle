#ifndef PUZZLE_COLORS_H
#define PUZZLE_COLORS_H

#include <string>
#include <cinder/gl/gl.h>

namespace PuzzleDemos {
    namespace Color {
        std::map<std::string, cinder::Color> get_solarized();
    }
}


#endif //PUZZLE_COLORS_H
