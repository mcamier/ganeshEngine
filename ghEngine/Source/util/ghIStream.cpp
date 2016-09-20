#include "util/ghIStream.hpp"

#include "util/ghStringId.hpp"
#include "util/ghSerializable.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <cstring>

using namespace std;

namespace ganeshEngine {

template<> bool writeToStream<int>(IStream& stream, const int& object) {
    stream.write(sizeof(int), (void*)&object);
    return true;
}

template<> bool writeToStream<string>(IStream& stream, const string &object) {
    int length = object.size();
    stream.write(sizeof(int), &length);
    stream.write(length * sizeof(char), (void*)object.c_str());
    return true;
}

template<> bool writeToStream<float>(IStream& stream, const float& object) {
    stream.write(sizeof(float), (void*)&object);
    return true;
}

template<> bool writeToStream<bool>(IStream& stream, const bool& object) {
    stream.write(sizeof(bool), (void*)&object);
    return true;
}

template<> bool writeToStream<stringId>(IStream& stream, const stringId& object) {
    stream.write(sizeof(stringId), (void*)&object);
    return true;
}

template<> bool writeToStream<glm::vec3>(IStream& stream, const glm::vec3& object) {
    stream.write(sizeof(float), (void*)&object.x);
    stream.write(sizeof(float), (void*)&object.y);
    stream.write(sizeof(float), (void*)&object.z);
    return true;
}

template<> bool writeToStream<std::vector<Serializable*>>(IStream& stream, const std::vector<Serializable*>& object) {
    return true;
}


template<> bool readFromStream<int>(IStream& stream, int &obj) {
    return (stream.read(sizeof(int), &obj) == sizeof(int));
}


template<> bool readFromStream<string>(IStream& stream, string &object) {
    int length = 0;
    stream.read(sizeof(int), &length);
    char* buffer = (char*)malloc(length);
    int byteRead = stream.read(length * sizeof(char), buffer);
    object = string(buffer);

    return byteRead == length;
}

template<> bool readFromStream<float>(IStream& stream, float &obj) {
    return (stream.read(sizeof(float), &obj) == sizeof(float));
}

template<> bool readFromStream<bool>(IStream& stream, bool &obj) {
    return (stream.read(sizeof(bool), &obj) == sizeof(bool));
}

template<> bool readFromStream<stringId>(IStream& stream, stringId &obj) {
    int read = stream.read(sizeof(stringId), &obj);
    return sizeof(stringId) == read;
}

template<> bool readFromStream<glm::vec3>(IStream& stream, glm::vec3 &obj) {
    size_t amoutRead = 0;
    amoutRead += stream.read(sizeof(float), &obj.x);
    amoutRead += stream.read(sizeof(float), &obj.y);
    amoutRead += stream.read(sizeof(float), &obj.z);
    return (amoutRead == (sizeof(float) + sizeof(float) + sizeof(float)));
}

}
