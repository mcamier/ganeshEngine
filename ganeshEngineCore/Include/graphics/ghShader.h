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
    friend class ShaderProgram;

private:
    /** This id comes from opengl once the shader was created on GC
     */
    GLuint mInternalId;

    /** The shader's type
     */
    ShaderType mType;

    /** The shader's status
     * After creation its value is NONE, should be COMPILED after a successful call
     * to doCompile, FAILED oterwise
     */
    ShaderStatus mStatus;

    /** The source code of the shader
     */
    string mSource;

public:
    Shader(ShaderType type, string source) :
            mInternalId(-1),
            mType(type),
            mStatus(ShaderStatus::NONE),
            mSource(source) {}

    ~Shader() {}

    static Shader* fromFile(ShaderType type, const char *filename);

    bool sendToGc() override;

    bool freeFromGc() override;

    /**
     *
     * @return shader's type
     */
    const ShaderType getType() const;

    /**
     *
     * @return shader's status
     */
    const ShaderStatus getStatus() const;
};


}

#endif //GANESHENGINE_GHSHADER_H
