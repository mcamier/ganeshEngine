#ifndef GANESHENGINE_GHGLTEXTURE_H
#define GANESHENGINE_GHGLTEXTURE_H

#include "../ghHeaders.h"
#include "graphics/ghHeaders.h"

#include "ghResource.h"

namespace ganeshEngine {

using namespace std;

class Texture : public Resource {
    friend class PngTextureLoader;

private:
    U32 mWidth;
    U32 mHeight;
    U32 mbitDepth;
    U32 mColorType;
    unsigned char *mImageData;

    /* opengl id used once texture is loaded */
    GLuint mTextureId = -1;

public:
    Texture() : Resource(true) {}

    U32 getWidth() const {
        return mWidth;
    }

    U32 getHeight() const {
        return mHeight;
    }

    U32 getBitDepth() const {
        return mbitDepth;
    }

    U32 getColorType() const {
        return mColorType;
    }

    bool sendToGc() override {
        Resource::sendToGc();
        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);
        glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*) mImageData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        return true;
    }

    bool freeFromGc() override {
        Resource::freeFromGc();
        glDeleteTextures(1,&mTextureId);
        return true; }
};

}

#endif //GANESHENGINE_GHGLTEXTURE_H
