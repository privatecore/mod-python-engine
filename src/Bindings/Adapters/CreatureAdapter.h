#ifndef MOD_PYTHON_ENGINE_CREATURE_ADAPTER_H
#define MOD_PYTHON_ENGINE_CREATURE_ADAPTER_H

#include "Creature.h"

namespace PyEng::CreatureAdapter
{
    inline uint32 GetGUIDLow(Creature* creature)
    {
        return creature ? creature->GetGUID().GetCounter() : 0;
    }

    inline void Respawn(Creature* creature)
    {
        if (creature)
            creature->Respawn();
    }

    inline void Say(Creature* creature, const std::string& text, uint32 language)
    {
        if (creature)
            creature->Say(text, static_cast<Language>(language));
    }

    inline void Yell(Creature* creature, const std::string& text, uint32 language)
    {
        if (creature)
            creature->Yell(text, static_cast<Language>(language));
    }

    inline void SetHomePosition(Creature* creature, float x, float y, float z, float o)
    {
        if (creature)
            creature->SetHomePosition(x, y, z, o);
    }

} // namespace PyEng::CreatureAdapter

#endif // MOD_PYTHON_ENGINE_CREATURE_ADAPTER_H
