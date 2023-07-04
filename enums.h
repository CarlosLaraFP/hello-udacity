#ifndef ENUMS_H
#define ENUMS_H

#include <iostream> // brings in <string> too

using std::cout;
using std::string;

enum class TileState {Free, Blocked};

string TileToString(const TileState& tile) {
    switch (tile) {
        case TileState::Free : return "0";
        case TileState::Blocked : return "X";
    }
}

#endif // ENUMS_H