#ifndef TYPES_H
#define TYPES_H

enum class TileState {
    Free, 
    Blocked,
    Closed,
    Path
};

struct Node {
    int x;
    int y;
    int g;
    int h;
};

#endif // TYPES_H