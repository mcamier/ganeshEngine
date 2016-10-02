#ifndef GANESHENGINE_GHINPUTAPI_H
#define GANESHENGINE_GHINPUTAPI_H

class IInputAPI {
public:
    /**
     *
     */
    virtual void vInitialize() = 0;

    /**
     *
     */
    virtual void vDestroy() = 0;
};

#endif //GANESHENGINE_GHINPUTAPI_H
