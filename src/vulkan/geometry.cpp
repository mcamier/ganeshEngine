#include "geometry.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "../input/inputManager.hpp"


using ge::input::InputManager;
using ge::input::inputKeyboardKey;

namespace ge {

std::vector<VkVertexInputAttributeDescription> VertexPosNormalColorTex::getAttributeDescriptions() {
    std::vector<VkVertexInputAttributeDescription> attributes(4);
    attributes[0].binding = 0;
    attributes[0].location = 0;
    attributes[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[0].offset = offsetof(VertexPosNormalColorTex, position);

    attributes[1].binding = 0;
    attributes[1].location = 1;
    attributes[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[1].offset = offsetof(VertexPosNormalColorTex, color);

    attributes[2].binding = 0;
    attributes[2].location = 2;
    attributes[2].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributes[2].offset = offsetof(VertexPosNormalColorTex, normal);

    attributes[3].binding = 0;
    attributes[3].location = 3;
    attributes[3].format = VK_FORMAT_R32G32_SFLOAT;
    attributes[3].offset = offsetof(VertexPosNormalColorTex, texCoord);

    return attributes;
}

Camera::Camera(glm::vec3 position, glm::vec3 sightTarget) {
    this->position = position;
    front = glm::normalize(sightTarget - this->position);
    glm::vec3 temp_up = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 right = glm::cross(temp_up, front);
    up = glm::normalize(glm::cross(front, right));

    viewDirty = true;
}

void Camera::update() {
    InputManager &inputManager = InputManager::get();

    if (inputManager.isKeyPressedOnce(inputKeyboardKey::INPUT_KEY_UP)) {
        position += cameraSpeed * front;
        viewDirty = true;
    }
    if (inputManager.isKeyPressedOnce(inputKeyboardKey::INPUT_KEY_DOWN)) {
        position -= cameraSpeed * front;
        viewDirty = true;
    }
    if (inputManager.isKeyPressedOnce(inputKeyboardKey::INPUT_KEY_LEFT)) {
        position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
        viewDirty = true;
    }
    if (inputManager.isKeyPressedOnce(inputKeyboardKey::INPUT_KEY_RIGHT)) {
        position += glm::normalize(glm::cross(front, up)) * cameraSpeed;
        viewDirty = true;
    }

}

glm::mat4 &Camera::getLookAt() {
    if (viewDirty) {
        view = glm::lookAt(position, position + front, up);
        viewDirty = false;
    }
    return view;
}


} // namespace ge