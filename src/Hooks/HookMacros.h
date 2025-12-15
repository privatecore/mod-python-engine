#ifndef MOD_PYTHON_ENGINE_HOOK_MACROS_H
#define MOD_PYTHON_ENGINE_HOOK_MACROS_H

#include "PythonEngine.h"
#include "HookDefines.h"

/**
 * @brief Convenience Macros for Triggering Hooks
 */

#define TRIGGER_ACCOUNT_HOOK(Hook, ...) \
    sPythonEngine->Trigger(PyEng::Hooks::Account::Hook, 0, ##__VA_ARGS__)

#define TRIGGER_PLAYER_HOOK(Hook, ...) \
    sPythonEngine->Trigger(PyEng::Hooks::Player::Hook, 0, ##__VA_ARGS__)

#define TRIGGER_CREATURE_HOOK(Hook, Entry, ...) \
    sPythonEngine->Trigger(PyEng::Hooks::Creature::Hook, Entry, ##__VA_ARGS__)

#define TRIGGER_GAMEOBJECT_HOOK(Hook, Entry, ...) \
    sPythonEngine->Trigger(PyEng::Hooks::GameObject::Hook, Entry, ##__VA_ARGS__)

#define TRIGGER_ITEM_HOOK(Hook, Entry, ...) \
    sPythonEngine->Trigger(PyEng::Hooks::Item::Hook, Entry, ##__VA_ARGS__)

#endif // MOD_PYTHON_ENGINE_HOOK_MACROS_H
