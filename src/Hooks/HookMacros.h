#ifndef MOD_PYTHON_ENGINE_HOOK_MACROS_H
#define MOD_PYTHON_ENGINE_HOOK_MACROS_H

#include "PythonEngine.h"
#include "HookInfo.h"

/**
 * @brief Convenience Macros for Triggering Hooks
 */

#define TRIGGER_ACCOUNT_HOOK(Hook, ...) \
    sPythonEngine->Trigger( \
        PyEng::Hooks::MakeHookInfo(PyEng::Hooks::AccountHook::Hook), \
        0, ##__VA_ARGS__)

#define TRIGGER_PLAYER_HOOK(Hook, ...) \
    sPythonEngine->Trigger( \
        PyEng::Hooks::MakeHookInfo(PyEng::Hooks::PlayerHook::Hook), \
        0, ##__VA_ARGS__)

#define TRIGGER_CREATURE_HOOK(Hook, Entry, ...) \
    sPythonEngine->Trigger( \
        PyEng::Hooks::MakeHookInfo(PyEng::Hooks::CreatureHook::Hook), \
        Entry, ##__VA_ARGS__)

#define TRIGGER_GAMEOBJECT_HOOK(Hook, Entry, ...) \
    sPythonEngine->Trigger( \
        PyEng::Hooks::MakeHookInfo(PyEng::Hooks::GameObjectHook::Hook), \
        Entry, ##__VA_ARGS__)

#define TRIGGER_ITEM_HOOK(Hook, Entry, ...) \
    sPythonEngine->Trigger( \
        PyEng::Hooks::MakeHookInfo(PyEng::Hooks::ItemHook::Hook), \
        Entry, ##__VA_ARGS__)

#endif // MOD_PYTHON_ENGINE_HOOK_MACROS_H
