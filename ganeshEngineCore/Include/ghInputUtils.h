#ifndef GANESHENGINE_GHINPUTUTILS_H
#define GANESHENGINE_GHINPUTUTILS_H

#include "ghHeaders.h"
#include <vector>

namespace ganeshEngine {

using namespace std;

/**
 * Supported input devices
 */
enum class rawInputSource {
    MOUSE,
    KEYBOARD,
    JOYSTICK
};

/**
 * Kind of input
 *
 * PRESS: when a button get pressed
 * RELEASE: when a button get released
 * HOLD: when a button was pressed last frame and is still pressed this frame
 * RANGE: value between 0 and 1, for instance the xbox controller triggers
 * MOVE: 3 dimensional floats
 */
enum class rawInputType {
    PRESS,
    RELEASE,
    HOLD,
    RANGE,
    MOVE
};

/**
 * Store informations for all inputs that can be either pressed,
 * released, or held (like keyboard keys, joysticks buttons or
 * mouse buttons)
 */
typedef struct buttonData_s {
    int key;
    int scancode;
    int mods;
    long duration;
} buttonData;

typedef struct rangeData_s {
    float x;
    float y;
    float z;
} rangeData;

typedef struct moveData_s {
    float x;
    float y;
    float z;
} moveData;


    /**
 * Store informations from an input got from the system input layer
 * (GLFW by the time, should be later available through interface)
 */
typedef struct rawInput_s {
    /**
     * From which device the input comes from
     */
    rawInputSource source;

    /**
     * Type of the received input
     */
    rawInputType type;

    /**
     * Time when input occured
     */
    long timestamp;

    /**
     * Index of the devices that generates the input
     *
     * @note will be unrelevant value for the keyboard or the mouse
     * device source but significant when multiple xbox controllers are
     * plugged in
     */
    int idx;

    /**
     * Payload informations
     */
    union datas_u {
        buttonData button;
        rangeData range;
        moveData move;
    } data;
} rawInput;


struct InputMatch {
    rawInputSource source;
    rawInputType type;

    int idx = 0;
    int key;
    int mods = 0;
};

}

#endif //GANESHENGINE_GHINPUTUTILS_H
