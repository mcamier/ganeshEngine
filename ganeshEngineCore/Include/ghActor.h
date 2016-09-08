#ifndef GANESHENGINE_GHACTOR_H
#define GANESHENGINE_GHACTOR_H

#include "ghHeaders.h"
#include "ghSceneObject.h"
#include "graphics/ghModel.h"

namespace ganeshEngine {

    class Actor : public SceneObject {

    private:
        Model *mModel{nullptr};

    public:
        Actor() : SceneObject(SceneObjectType::ACTOR) {}

        virtual ~Actor() {}

        void setModel(Model *model);

        Model *getModel() const;

        void preRender() override;

        void render() override;

        void postRender() override;
    };

}

#endif //GANESHENGINE_GHACTOR_H
