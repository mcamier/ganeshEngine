#ifndef GANESHENGINE_GHGLMODEL_H
#define GANESHENGINE_GHGLMODEL_H


#include "ghShaderProgram.hpp"
#include "ghMesh.hpp"
#include "ghTexture.hpp"
#include "ghShader.hpp"

#include "resource/ghResourceHandler.hpp"

namespace ganeshEngine {

using namespace std;
using namespace glm;


class Model {
private:
    /** The shader program used to draw the geometry */
    ResourceHandler<ShaderProgram> mpProgram;

    /** The mesh to draw */
    ResourceHandler<Mesh> mpMesh;

    /** Optional texture to apply on the mesh */
    ResourceHandler<Texture> mpTexture;

    /** opengl internal id */
    //GLuint mVAO;
    int mVAO;

public:
    Model(ResourceHandler<ShaderProgram> program, ResourceHandler<Mesh> mesh, ResourceHandler<Texture> texture) :
            mpProgram(program),
            mpMesh(mesh),
            mpTexture(texture) {}

    ~Model() {}

    /* TODO rename this method in order to avoid confusion with loading in GC method of Resource class */
    /** Load the model into the GC memory to use it during the drawing */
    void sendToGC();

    ResourceHandler<ShaderProgram> getProgram();

    void preRender();
    void render();
    void postRender();

};

}

#endif //GANESHENGINE_GHGLMODEL_H
