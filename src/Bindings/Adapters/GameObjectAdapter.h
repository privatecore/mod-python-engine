#ifndef MOD_PYTHON_ENGINE_GAMEOBJECT_ADAPTER_H
#define MOD_PYTHON_ENGINE_GAMEOBJECT_ADAPTER_H

#include "GameObject.h"

namespace PyEng::GameObjectAdapter
{
    inline uint32 GetGUIDLow(GameObject* go)
    {
        return go ? go->GetGUID().GetCounter() : 0;
    }

    inline void Respawn(GameObject* go)
    {
        if (go)
            go->Respawn();
    }

    inline void Use(GameObject* go, Unit* unit)
    {
        if (go)
            go->Use(unit);
    }

} // namespace PyEng::GameObjectAdapter

#endif // MOD_PYTHON_ENGINE_GAMEOBJECT_ADAPTER_H
