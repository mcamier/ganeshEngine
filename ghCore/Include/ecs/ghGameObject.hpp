#ifndef GANESHENGINE_GHGAMEOBJECT_H
#define GANESHENGINE_GHGAMEOBJECT_H

#include "../ghTypes.hpp"
#include "../util/ghSerializable.hpp"
#include "../util/ghIStream.hpp"
#include "../util/ghRTTI.hpp"
#include "../ghWorld.hpp"

namespace ganeshEngine {

/**
 * Every object used within the gameplay must inherit this class. Each game object has an unique id used to be
 * queried and must provided RTTI informations
 * @see ghRTTI.h to know more about RTTI facility.
 */
class GameObject : public Serializable {

RTTI_DECL()

private:
    /** unique id, its unique-ness is not enforce by this class */
    U32 mUID;


protected:
    /**
     * Pointer of the world where this actor is registered
     * Is nullptr if the actor is not bound to any game world, otherwise we can expect the actor to be well bound
     */
    World* mOwnerWorld;

public:
    explicit GameObject(U32 uid);

    virtual ~GameObject();

    /**
     * Getter to the unique id
     * @return the unique id of the game object
     */
    U32 getUID() const;

    virtual bool write(IStream& stream) const override;

    virtual bool read(IStream& stream) override;
};

}

#endif //GANESHENGINE_GHGAMEOBJECT_H
