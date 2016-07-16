#ifndef GANESHENGINE_GHINPUTUTILS_H
#define GANESHENGINE_GHINPUTUTILS_H

#include "ghHeaders.h"

namespace ganeshEngine {

enum class rawInputSource {
    MOUSE,
    KEYBOARD,
    JOYSTICK
};

enum class rawInputType {
    PRESS,
    RELEASE,
    STATE,
    RANGE,
    MOVE
};

typedef struct mouseData_s {
    double x;
    double y;
} mouseData;

typedef struct mouseButtonData_s {
    int button;
    int action;
    int mods;
} mouseButtonData;

typedef struct keyboardData_s {
    int key;
    int scancode;
    int action;
    int mods;
} keyboardData;

typedef struct rawInput_s {
    rawInputSource source;
    rawInputType type;
    long timestamp;
    union datas_u {
        mouseData mouse;
        mouseButtonData button;
        keyboardData keyboard;
    } data;
} rawInput;
}

#endif //GANESHENGINE_GHINPUTUTILS_H
