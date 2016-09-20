#ifndef GANESHENGINE_GHBASICSTREAM_H
#define GANESHENGINE_GHBASICSTREAM_H

#include <cstdio>
#include <string>

#include "ghIStream.hpp"

namespace ganeshEngine {

using namespace std;

class BasicStream : public IStream {

private:
    std::string mFilename;
    FILE *mpFile;
    bool mbOpened;
    bool mbReadAccess;

public:
    BasicStream(std::string &filename) :
        mFilename(filename),
        mpFile(nullptr),
        mbOpened(false),
        mbReadAccess(true) {}

    BasicStream(const char *filename) :
        mFilename(string(filename)),
        mpFile(nullptr),
        mbOpened(false),
        mbReadAccess(true) {}

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

    bool open() {
        mpFile = fopen(mFilename.c_str(), "rb");
        if(mpFile == nullptr) {
            mpFile = fopen(mFilename.c_str(), "ab");
            mbReadAccess = false;
        }

        if(mpFile == nullptr) {
            mbOpened = true;
            return false;
        }
        return true;
    }

    bool close() {
        if(mpFile != nullptr) {
            fclose(mpFile);
            mbOpened = false;
            return true;
        }
        return false;
    }

    void reset() {}
};

}

#endif //GANESHENGINE_GHBASICSTREAM_H
