#ifndef GANESHENGINE_GHINPUTUTILS_H
#define GANESHENGINE_GHINPUTUTILS_H

#include "ghHeaders.h"
#include <vector>
#include <functional>

// TODO missing xbox controller keys
// TODO missing mouse button keys
#define GH_BUTTON_UNKNOWN   -1

#define GH_BUTTON_MOUSE_LEFT        1001
#define GH_BUTTON_MOUSE_RIGHT       1002

#define GH_BUTTON_KEY_APOSTROPHE    39 /* ' */
#define GH_BUTTON_KEY_COMMA         44 /* , */
#define GH_BUTTON_KEY_MINUS         45 /* - */
#define GH_BUTTON_KEY_PERIOD        46 /* . */
#define GH_BUTTON_KEY_SLASH         47 /* / */
#define GH_BUTTON_KEY_0             48
#define GH_BUTTON_KEY_1             49
#define GH_BUTTON_KEY_2             50
#define GH_BUTTON_KEY_3             51
#define GH_BUTTON_KEY_4             52
#define GH_BUTTON_KEY_5             53
#define GH_BUTTON_KEY_6             54
#define GH_BUTTON_KEY_7             55
#define GH_BUTTON_KEY_8             56
#define GH_BUTTON_KEY_9             57
#define GH_BUTTON_KEY_SEMICOLON     59 /* ; */
#define GH_BUTTON_KEY_EQUAL         61 /* = */
#define GH_BUTTON_KEY_A             65
#define GH_BUTTON_KEY_B             66
#define GH_BUTTON_KEY_C             67
#define GH_BUTTON_KEY_D             68
#define GH_BUTTON_KEY_E             69
#define GH_BUTTON_KEY_F             70
#define GH_BUTTON_KEY_G             71
#define GH_BUTTON_KEY_H             72
#define GH_BUTTON_KEY_I             73
#define GH_BUTTON_KEY_J             74
#define GH_BUTTON_KEY_K             75
#define GH_BUTTON_KEY_L             76
#define GH_BUTTON_KEY_M             77
#define GH_BUTTON_KEY_N             78
#define GH_BUTTON_KEY_O             79
#define GH_BUTTON_KEY_P             80
#define GH_BUTTON_KEY_Q             81
#define GH_BUTTON_KEY_R             82
#define GH_BUTTON_KEY_S             83
#define GH_BUTTON_KEY_T             84
#define GH_BUTTON_KEY_U             85
#define GH_BUTTON_KEY_V             86
#define GH_BUTTON_KEY_W             87
#define GH_BUTTON_KEY_X             88
#define GH_BUTTON_KEY_Y             89
#define GH_BUTTON_KEY_Z             90
#define GH_BUTTON_KEY_LEFT_BRACKET  91 /* [ */
#define GH_BUTTON_KEY_BACKSLASH     92 /* \ */
#define GH_BUTTON_KEY_RIGHT_BRACKET 93 /* ] */
#define GH_BUTTON_KEY_GRAVE_ACCENT  96 /* ` */
#define GH_BUTTON_KEY_WORLD_1       161 /* non-US #1 */
#define GH_BUTTON_KEY_WORLD_2       162 /* non-US #2 */
#define GH_BUTTON_KEY_ESCAPE        256
#define GH_BUTTON_KEY_ENTER         257
#define GH_BUTTON_KEY_TAB           258
#define GH_BUTTON_KEY_BACKSPACE     259
#define GH_BUTTON_KEY_INSERT        260
#define GH_BUTTON_KEY_DELETE        261
#define GH_BUTTON_KEY_RIGHT         262
#define GH_BUTTON_KEY_LEFT          263
#define GH_BUTTON_KEY_DOWN          264
#define GH_BUTTON_KEY_UP            265
#define GH_BUTTON_KEY_PAGE_UP       266
#define GH_BUTTON_KEY_PAGE_DOWN     267
#define GH_BUTTON_KEY_HOME          268
#define GH_BUTTON_KEY_END           269
#define GH_BUTTON_KEY_CAPS_LOCK     280
#define GH_BUTTON_KEY_SCROLL_LOCK   281
#define GH_BUTTON_KEY_NUM_LOCK      282
#define GH_BUTTON_KEY_PRINT_SCREEN  283
#define GH_BUTTON_KEY_PAUSE         284
#define GH_BUTTON_KEY_F1            290
#define GH_BUTTON_KEY_F2            291
#define GH_BUTTON_KEY_F3            292
#define GH_BUTTON_KEY_F4            293
#define GH_BUTTON_KEY_F5            294
#define GH_BUTTON_KEY_F6            295
#define GH_BUTTON_KEY_F7            296
#define GH_BUTTON_KEY_F8            297
#define GH_BUTTON_KEY_F9            298
#define GH_BUTTON_KEY_F10           299
#define GH_BUTTON_KEY_F11           300
#define GH_BUTTON_KEY_F12           301
#define GH_BUTTON_KEY_F13           302
#define GH_BUTTON_KEY_F14           303
#define GH_BUTTON_KEY_F15           304
#define GH_BUTTON_KEY_F16           305
#define GH_BUTTON_KEY_F17           306
#define GH_BUTTON_KEY_F18           307
#define GH_BUTTON_KEY_F19           308
#define GH_BUTTON_KEY_F20           309
#define GH_BUTTON_KEY_F21           310
#define GH_BUTTON_KEY_F22           311
#define GH_BUTTON_KEY_F23           312
#define GH_BUTTON_KEY_F24           313
#define GH_BUTTON_KEY_F25           314
#define GH_BUTTON_KEY_KP_0          320
#define GH_BUTTON_KEY_KP_1          321
#define GH_BUTTON_KEY_KP_2          322
#define GH_BUTTON_KEY_KP_3          323
#define GH_BUTTON_KEY_KP_4          324
#define GH_BUTTON_KEY_KP_5          325
#define GH_BUTTON_KEY_KP_6          326
#define GH_BUTTON_KEY_KP_7          327
#define GH_BUTTON_KEY_KP_8          328
#define GH_BUTTON_KEY_KP_9          329
#define GH_BUTTON_KEY_KP_DECIMAL    330
#define GH_BUTTON_KEY_KP_DIVIDE     331
#define GH_BUTTON_KEY_KP_MULTIPLY   332
#define GH_BUTTON_KEY_KP_SUBTRACT   333
#define GH_BUTTON_KEY_KP_ADD        334
#define GH_BUTTON_KEY_KP_ENTER      335
#define GH_BUTTON_KEY_KP_EQUAL      336
#define GH_BUTTON_KEY_LEFT_SHIFT    340
#define GH_BUTTON_KEY_LEFT_CONTROL  341
#define GH_BUTTON_KEY_LEFT_ALT      342
#define GH_BUTTON_KEY_LEFT_SUPER    343
#define GH_BUTTON_KEY_RIGHT_SHIFT   344
#define GH_BUTTON_KEY_RIGHT_CONTROL 345
#define GH_BUTTON_KEY_RIGHT_ALT     346
#define GH_BUTTON_KEY_RIGHT_SUPER   347
#define GH_BUTTON_KEY_MENU          348
#define GH_BUTTON_KEY_LAST          GLFW_KEY_MENU

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


/**
 *
 */
class InputMatch {

private:
    int m_id;
    static int m_lastId;

public:
    rawInputSource source;
    rawInputType type;

    int key;
    int mods = 0;

    InputMatch();
    InputMatch(const InputMatch&) = delete;
    InputMatch& operator=(const InputMatch&) = delete;

    int getId();
};

}

#endif //GANESHENGINE_GHINPUTUTILS_H
