#ifndef GANESHENGINE_GHBASICSTREAM_H
#define GANESHENGINE_GHBASICSTREAM_H

#include <cstdio>
#include <string>

#include "ghIStream.h"

namespace ganeshEngine {

using namespace std;

class BasicStream : public IStream {

private:
    FILE *mpFile;
    std::string mFilename;
    bool mbReadAccess;

public:
    BasicStream(std::string &filename) {
        mpFile = fopen(filename.c_str(), "rb");
        mbReadAccess = true;
        if(mpFile == nullptr) {
            mpFile = fopen(filename.c_str(), "ab");
            mbReadAccess = false;
        }
        mFilename = filename;
    }

    BasicStream(const char *filename) {
        mpFile = fopen(filename, "rb");
        mbReadAccess = true;
        if(mpFile == nullptr) {
            mpFile = fopen(filename, "ab");
            mbReadAccess = false;
        }
        mFilename = string(filename);
    }

    void reset() {}

    int read(int size, void* buffer) override {
        if(mpFile == nullptr) {
            return 0;
        }

        if(!mbReadAccess) {
            freopen(mFilename.c_str(), "rb", mpFile);
            if(mpFile == nullptr) {
                return 0;
            }
        }
        return fread(buffer, 1, size, mpFile);
    }

    int write(int size, void* buffer) override {
        if(mpFile == nullptr) {
            return 0;
        }

        if(mbReadAccess) {
            freopen(mFilename.c_str(), "ab", mpFile);
            if(mpFile == nullptr) {
                return 0;
            }
            mbReadAccess = false;
        }
        return fwrite(buffer, 1, size, mpFile);
    }

    void close() {
        if(mpFile != nullptr) {
            fclose(mpFile);
        }

    }
};

}

#endif //GANESHENGINE_GHBASICSTREAM_H
