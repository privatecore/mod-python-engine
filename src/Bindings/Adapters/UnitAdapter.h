#ifndef MOD_PYTHON_ENGINE_UNIT_ADAPTER_H
#define MOD_PYTHON_ENGINE_UNIT_ADAPTER_H

#include "Unit.h"

namespace PyEng::UnitAdapter
{
    inline uint32 GetGUIDLow(Unit* unit)
    {
        return unit ? unit->GetGUID().GetCounter() : 0;
    }

} // namespace PyEng::UnitAdapter

#endif // MOD_PYTHON_ENGINE_UNIT_ADAPTER_H
