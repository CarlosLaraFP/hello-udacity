#ifndef TYPES_H
#define TYPES_H

enum class TileState {
    Free, 
    Blocked,
    Closed
};

struct Node {
    int x;
    int y;
    int g;
    int h;
};

#endif // TYPES_H