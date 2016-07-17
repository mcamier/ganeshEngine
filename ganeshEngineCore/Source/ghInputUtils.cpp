#include "ghInputUtils.h"

namespace ganeshEngine {

int InputMatch::m_lastId = 0;

InputMatch::InputMatch() {
    m_id = m_lastId++;
}

int InputMatch::getId() {
    return m_id;
}

}