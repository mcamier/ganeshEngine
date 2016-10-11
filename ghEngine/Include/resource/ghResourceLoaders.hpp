#ifndef GANESHENGINE_GHRESOURCELOADERS_H
#define GANESHENGINE_GHRESOURCELOADERS_H

#include "ghResourceLoader.hpp"

#include "ghResourceManager.hpp"

#include <util/ghStringId.hpp>
#include "../render/ghTexture.hpp"
#include "../render/ghMesh.hpp"
#include "../render/ghShaderProgram.hpp"
#include "../render/ghShader.hpp"

#ifdef NODEF
#include <png.h>
#endif //NODEF

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>
#include <fstream>

#include <glm/glm.hpp>
#include <util/ghILogger.hpp>

namespace ganeshEngine {

using namespace glm;
using namespace rapidjson;
using namespace std;

static stringId ghTextureLoaderName         = gInternString("__TEXTURE_PNG_LOADER");
static stringId ghObjLoaderName             = gInternString("__MESH_OBJ_LOADER");
static stringId ghShaderLoaderName          = gInternString("__SHADER_LOADER");
static stringId ghShaderProgramLoaderName   = gInternString("__SHADER_PROGRAM_LOADER");

class PngTextureLoader : public ResourceLoader {

public:
    /**
     * Load a file as a png resource
     * @note the code of this methods comes from :
     * https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures#A_simple_libpng_example
     *
     * @param infos
     * @return unique_ptr to the loaded resource or nullptr in case of error
     */
    unique_ptr<Resource> load(const ResourceInfos &infos) const override {
        Texture *t = new Texture();
#ifdef NODEF
        png_byte header[8];

        //open file as binary
        FILE *fp = fopen(infos.getFilename().c_str(), "rb");
        if (!fp) {
            return nullptr;
        }

        //read the header
        fread(header, 1, 8, fp);

        //test if png
        int is_png = !png_sig_cmp(header, 0, 8);
        if (!is_png) {
            fclose(fp);
            return nullptr;
        }

        //create png struct
        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!png_ptr) {
            fclose(fp);
            return nullptr;
        }

        //create png info struct
        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr) {
            png_destroy_read_struct(&png_ptr, (png_infopp) nullptr, (png_infopp) nullptr);
            fclose(fp);
            return nullptr;
        }

        //create png info struct
        png_infop end_info = png_create_info_struct(png_ptr);
        if (!end_info) {
            png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) nullptr);
            fclose(fp);
            return nullptr;
        }

        //png error stuff, not sure libpng man suggests this.
        if (setjmp(png_jmpbuf(png_ptr))) {
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            return nullptr;
        }

        //init png reading
        png_init_io(png_ptr, fp);

        //let libpng know you already read the first 8 bytes
        png_set_sig_bytes(png_ptr, 8);

        // read all the info up to the image data
        png_read_info(png_ptr, info_ptr);

        //variables to pass to get info
        int bit_depth, color_type;
        png_uint_32 twidth, theight;

        // get info about png
        png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type, nullptr, nullptr, nullptr);

        //update width and height based on png info
        t->mWidth = twidth;
        t->mHeight = theight;
        t->mColorType = color_type;
        t->mbitDepth = bit_depth;

        // Update the png info struct.
        png_read_update_info(png_ptr, info_ptr);

        // Row size in bytes.
        int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

        // Allocate the image_data as a big block, to be given to opengl
        png_byte *image_data = new png_byte[rowbytes * theight];
        if (!image_data) {
            //clean up memory and close stuff
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            return nullptr;
        }
        t->mImageData = image_data;

        //row_pointers is for pointing to image_data for reading the png with libpng
        png_bytep *row_pointers = new png_bytep[theight];
        if (!row_pointers) {
            //clean up memory and close stuff
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            delete[] image_data;
            fclose(fp);
            return nullptr;
        }
        // set the individual row_pointers to point at the correct offsets of image_data
        for (U32 i = 0; i < theight; ++i)
            row_pointers[theight - 1 - i] = image_data + i * rowbytes;

        //read the png into image_data through row_pointers
        png_read_image(png_ptr, row_pointers);

        //clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete[] row_pointers;
        fclose(fp);
#endif //NODEF
        return unique_ptr<Resource>(t);
    }
};


class ObjModelLoader : public ResourceLoader {
public:
    unique_ptr<Resource> load(const ResourceInfos &infos) const override {
        Mesh *m = new Mesh();

        std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
        std::vector< glm::vec3 > temp_vertices;
        std::vector< glm::vec2 > temp_uvs;
        std::vector< glm::vec3 > temp_normals;

        vector<float> buffer;

        FILE * file = fopen(infos.getFilename().c_str(), "r");
        if( file == NULL ){
            printf("Impossible to open the file !\n");
            return nullptr;
        }

        while( 1 ) {

            char lineHeader[128];
            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF) {
                break; // EOF = End Of File. Quit the loop.
            }
            if ( strcmp( lineHeader, "v" ) == 0 ){
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
                temp_vertices.push_back(vertex);
            }else if ( strcmp( lineHeader, "vt" ) == 0 ){
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y );
                temp_uvs.push_back(uv);
            }else if ( strcmp( lineHeader, "vn" ) == 0 ){
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                temp_normals.push_back(normal);
            }else if ( strcmp( lineHeader, "f" ) == 0 ) {
                unsigned int vertexIndex[3], normalIndex[3];
                fscanf(file, "%u//%u %u//%u %u//%u\n",
                       &vertexIndex[0], &normalIndex[0],
                       &vertexIndex[1], &normalIndex[1],
                       &vertexIndex[2], &normalIndex[2]);

                for(int i = 0 ; i < 3 ; i++) {
                    m->mBuffer.push_back(temp_vertices[vertexIndex[i]].x);
                    m->mBuffer.push_back(temp_vertices[vertexIndex[i]].y);
                    m->mBuffer.push_back(temp_vertices[vertexIndex[i]].z);
                    m->mBuffer.push_back(temp_normals[normalIndex[i]].x);
                    m->mBuffer.push_back(temp_normals[normalIndex[i]].y);
                    m->mBuffer.push_back(temp_normals[normalIndex[i]].z);
                }
            }
        }

        _DEBUG("load mesh buffer with " << buffer.size() << " entries", LOG_CHANNEL::DEFAULT);
        m->mDrawMode = DrawMode::TRIANGLES;
        return unique_ptr<Resource>(m);
    }
};

class ShaderLoader : public ResourceLoader {
public:
    unique_ptr<Resource> load(const ResourceInfos &infos) const override {
        auto itr = infos.getMetadatas().find(gInternString("stage"));
        if(itr == infos.getMetadatas().end()) {
            _ERROR("The metadata 'stage' is required in order to load a Shader", LOG_CHANNEL::RESOURCE);
            return nullptr;
        }
        const char* stage = itr->second.value.asString;

        ShaderType type;
        if(std::strcmp(stage, "vertex") == 0) {// TODO Error #4: UNADDRESSABLE ACCESS beyond heap bounds: 1 byte
            type = ShaderType::VERTEX;
        }
        else if(std::strcmp(stage, "fragment") == 0) {// TODO Error #4: UNADDRESSABLE ACCESS beyond heap bounds: 1 byte
            type = ShaderType::FRAGMENT;
        }
        else {
            _ERROR("The metadata 'stage' doesn't contains an expected value", LOG_CHANNEL::RESOURCE);
            return nullptr;
        }

        Shader *s = new Shader();

        std::ifstream t{infos.getFilename().c_str()};
        std::string content;

        t.seekg(0, std::ios::end);
        content.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        s->mType = type;
        content.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        s->mSource = content;

        return unique_ptr<Shader>(s);
    }
};

class ShaderProgramLoader : public ResourceLoader {

public:
    unique_ptr<Resource> load(const ResourceInfos &infos) const override {
        auto vres = infos.getDependencies().find(gInternString("vertex"));
        auto fres = infos.getDependencies().find(gInternString("fragment"));

        if (vres == infos.getDependencies().end() || fres == infos.getDependencies().end()) {
            _ERROR("The metadatas 'vertex' and 'fragment' are both required in order to load a ShaderProgram", LOG_CHANNEL::RESOURCE);
            return nullptr;
        }

        ResourceHandler<Shader> vertex = gResource().getResource<Shader>(vres->second);
        ResourceHandler<Shader> fragment = gResource().getResource<Shader>(fres->second);

        if(vertex == nullptr || fragment == nullptr) {
            return nullptr;
        }

        ShaderProgram *sp = new ShaderProgram(vertex, fragment);
        return unique_ptr<ShaderProgram>(sp);
    }
};

}

#endif //GANESHENGINE_GHRESOURCELOADERS_H
