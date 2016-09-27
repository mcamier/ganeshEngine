#ifndef GANESHENGINE_GHISTREAM_H
#define GANESHENGINE_GHISTREAM_H

namespace ganeshEngine {

class IStream {
public:
    virtual ~IStream() {}

    virtual bool open() = 0;
    virtual int read(int size, void* buffer) = 0;
    virtual int write(int size, void* buffer) = 0;
    virtual bool close() = 0;
    virtual void reset() = 0;
};

template<typename T> bool readFromStream(IStream& stream, T& obj);
template<typename T> bool writeToStream(IStream& stream, const T& object);

}

#endif //GANESHENGINE_GHISTREAM_H
