#ifndef GANESHENGINE_GHRESOURCELOADERS_H
#define GANESHENGINE_GHRESOURCELOADERS_H

#include "ghResourceLoader.h"

#include "graphics/ghTexture.h"
#include "graphics/ghMesh.h"
#include "graphics/ghShaderProgram.h"
#include "graphics/ghShader.h"

#include <png.h>

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>

namespace ganeshEngine {

using namespace rapidjson;
using namespace std;


class PngTextureLoader : public ResourceLoader {

public:
    /**
     * Load a file as a png resource
     * @note the code of this methods comes from :
     * https://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures#A_simple_libpng_example
     *
     * @param filename filename of the png file to load
     * @return unique_ptr to the loaded resource or nullptr in case of error
     */
    unique_ptr<Resource> load(const char *filename) const override {
        Texture *t = new Texture();
        png_byte header[8];

        //open file as binary
        FILE *fp = fopen(filename, "rb");
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
        for (int i = 0; i < theight; ++i)
            row_pointers[theight - 1 - i] = image_data + i * rowbytes;

        //read the png into image_data through row_pointers
        png_read_image(png_ptr, row_pointers);

        //clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete[] row_pointers;
        fclose(fp);

        return unique_ptr<Resource>(t);
    }
};

class ObjModelLoader : public ResourceLoader {
public:
    unique_ptr<Resource> load(const char *filename) const override {
        Mesh *m = new Mesh();
        return unique_ptr<Resource>(m);
    }
};

class ShaderLoader : public ResourceLoader {
public:
    unique_ptr<Resource> load(const char *filename) const override {
        //check presence of metadata type, fail if missing
        // fail if value is not vertex or fragment
    }
};


class ShaderProgramLoader : public ResourceLoader {
public:
    unique_ptr<Resource> load(const char *filename) const override {
    }
};

}

#endif //GANESHENGINE_GHRESOURCELOADERS_H
