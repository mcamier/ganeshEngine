#include "ghResourceImporter.h"
#include "ghResource.h"

namespace ganeshEngine {

void *ResourceLoader::typenameload(Resource &resource) {
    void *base = static_cast<void *>(specificLoad(resource));
    if (base == nullptr) {
        _WARNING("fail to importer resource : " << filename, LOG_CHANNEL::DEFAULT);
    }
    return base;
}


GLShader *GLShaderResourceLoader::specificLoad(Resource &resource) {
    const string* type = resource.getMetadata("shaderType");
    ShaderType shaderType;
    if(type->compare("fragment") == 0) {
        shaderType = ShaderType::FRAGMENT;
    } else if(type->compare("vertex") == 0) {
        shaderType = ShaderType::VERTEX;
    } else {
        _ERROR("shaderType metadata needed", LOG_CHANNEL::DEFAULT);
    }
    return GLShader::fromFile(shaderType, filename.c_str());
}

GLProgram *GLProgramResourceLoader::specificLoad(Resource &resource) {
    return nullptr;
}

}
