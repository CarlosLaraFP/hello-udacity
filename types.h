#ifndef TYPES_H
#define TYPES_H

enum class TileState {
    Free, 
    Blocked,
    Closed,
    Path,
    Start,
    Finish
};

struct Coordinate {
    int x;
    int y;
};

struct Node {
    Coordinate c;
    int g;
    int h;
};

#endif // TYPES_H