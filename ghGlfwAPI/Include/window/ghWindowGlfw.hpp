#ifndef GANESHENGINE_WINDOWGLFW_H
#define GANESHENGINE_WINDOWGLFW_H

#include <window/ghIWindow.hpp>

namespace ganeshEngine {

class ghWindowGlfw : public IWindow {

    public:
    ghWindowGlfw();

    ~ghWindowGlfw();

    void vInitialize();

    void vDestroy();
};

}

#endif