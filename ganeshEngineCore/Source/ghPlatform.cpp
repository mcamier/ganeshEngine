#include "ghPlatform.h"

#include <thread>

namespace ganeshEngine {

using namespace std;

const U16 Platform::getScreenHeight() {
    return 0;
}

const U16 Platform::getScreenWidth() {
    return 0;
}

const U16 Platform::getScreenRefreshRate() {
    return 0;
}

const U16 Platform::getCpuCoreAmount() {
    return thread::hardware_concurrency();
}

}