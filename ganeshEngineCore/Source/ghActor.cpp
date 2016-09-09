#include "ghActor.h"
#include "ghScene.h"
#include "ghCamera.h"

namespace ganeshEngine {


    void Actor::setModel(Model *model) {
        mModel = model;
    }

    Model *Actor::getModel() const {
        return mModel;
    }


    void Actor::preRender() {
        SceneObject::preRender();
    }

    void Actor::render() {
        mModel->preRender();
        //mModel->getProgram()->setUniform("gh_u_modelview_mat", this->getTransform());
        //mModel->getProgram()->setUniform("gh_u_eye_mat", mOwner->getCamera()->getEyeMatrix());
        //mModel->getProgram()->setUniform("gh_u_projection_mat", mOwner->getCamera()->getProjection());
        mModel->render();
        mModel->postRender();

        SceneObject::render();
    }

    void Actor::postRender() {
        SceneObject::postRender();
    }

}