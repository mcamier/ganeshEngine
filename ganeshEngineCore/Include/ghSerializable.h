#ifndef GANESHENGINE_GHSERIALIZABLE_H
#define GANESHENGINE_GHSERIALIZABLE_H

#include "ghHeaders.h"
#include "ghIStream.h"

namespace ganeshEngine {

class Serializable {
public:
    virtual bool write(IStream& stream) const = 0;
    virtual bool read(IStream& stream) = 0;
};

}

#endif //GANESHENGINE_GHSERIALIZABLE_H
