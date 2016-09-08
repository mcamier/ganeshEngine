#ifndef GANESHENGINE_GHGLMODEL_H
#define GANESHENGINE_GHGLMODEL_H

#include "graphics/ghHeaders.h"
#include "graphics/ghShaderProgram.h"
#include "graphics/ghMesh.h"
#include "graphics/ghTexture.h"
#include "graphics/ghShader.h"

namespace ganeshEngine {

using namespace std;
using namespace glm;


class Model {
private:
    /** The shader program used to draw the geometry
     */
    ShaderProgram *mpProgram;

    /** The mesh to draw
     */
    Mesh *mpMesh;

    /** Optional texture to apply on the mesh
     */
    Texture *mpTexture;

    /** The id of Vertex Array Object
     */
    GLuint mVAO;

public:
    Model(ShaderProgram *program, Mesh *mesh, Texture *texture) :
            mpProgram(program), mpMesh(mesh), mpTexture(texture) {}

    ~Model() {}

    /**
     * Load the model into the GC memory to use it during the drawing
     */
    void sendToGC();

    ShaderProgram *getProgram();

    void preRender();

    void render();

    void postRender();

};

}

#endif //GANESHENGINE_GHGLMODEL_H
