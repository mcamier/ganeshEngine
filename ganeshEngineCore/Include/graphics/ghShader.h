#ifndef GANESHENGINE_GHSHADER_H
#define GANESHENGINE_GHSHADER_H

#include "../ghHeaders.h"
#include "ghHeaders.h"
#include "../ghResource.h"

#include <GL/glew.h>

namespace ganeshEngine {

using namespace std;

class ShaderProgram;


class Shader : public Resource {
    friend class ShaderLoader;
    friend class ShaderProgram;

private:
    /** This id comes from opengl once the shader was created on GC
     */
    GLuint mInternalId;

    /** The shader's type
     */
    ShaderType mType;

    /** The source code of the shader
     */
    string mSource;

public:
    Shader() : mInternalId(-1), mSource(""), Resource(true) {}
    ~Shader() {}

    /**
     *
     * @return shader's type
     */
    const ShaderType getType() const;

protected:
    bool sendToGc() override;

    bool freeFromGc() override;
};


}

#endif //GANESHENGINE_GHSHADER_H
