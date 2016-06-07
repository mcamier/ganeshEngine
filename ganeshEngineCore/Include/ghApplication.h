#ifndef GANESHENGINE_GHAPPLICATION_H
#define GANESHENGINE_GHAPPLICATION_H

#include "ghHeaders.h"
#include "ghSystem.h"
#include "ghClock.h"

namespace ganeshEngine {

/** The entry point of the engine
 */
class Application : public System<Application> {

    friend class System<Application>;

    Clock mMainClock;
    bool mIsExiting;

    Application() : mIsExiting(false) {}

public:
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    ~Application() {}

    /** Run the lifecycle of the engine
     *  It's a static stub used to call the instance's member
     */
    static void RunLoop();

    /** shutdown the main loop
     */
    void shutdown();

protected:
    /** Responsible of the initialization of all subsystems
     */
    void vInitialize() override;

    /** Responsible of the destruction of all subsystems
     */
    void vDestroy() override;

    /** the main loop logic
     */
    void run();
};

extern Application&(*gApp)();
}


#endif //GANESHENGINE_GHAPPLICATION_H
