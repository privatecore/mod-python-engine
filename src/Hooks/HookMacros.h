#ifndef MOD_PYTHON_ENGINE_HOOK_MACROS_H
#define MOD_PYTHON_ENGINE_HOOK_MACROS_H

#include "HookInfo.h"

/**
 * @brief Convenience Macros for Triggering Hooks
 */
#define TRIGGER_ACCOUNT_HOOK(Hook, ...) \
    sPythonEngine->Trigger(MakeHookInfo(Hooks::AccountHook::Hook), 0, ##__VA_ARGS__)

#define TRIGGER_PLAYER_HOOK(Hook, ...) \
    sPythonEngine->Trigger(MakeHookInfo(Hooks::PlayerHook::Hook), 0, ##__VA_ARGS__)

#define TRIGGER_CREATURE_HOOK(Hook, Entry, ...) \
    sPythonEngine->Trigger(MakeHookInfo(Hooks::CreatureHook::Hook), Entry, ##__VA_ARGS__)

#define TRIGGER_GAMEOBJECT_HOOK(Hook, Entry, ...) \
    sPythonEngine->Trigger(MakeHookInfo(Hooks::GameObjectHook::Hook), Entry, ##__VA_ARGS__)

#define TRIGGER_ITEM_HOOK(Hook, Entry, ...) \
    sPythonEngine->Trigger(MakeHookInfo(Hooks::ItemHook::Hook), Entry, ##__VA_ARGS__)

#endif // MOD_PYTHON_ENGINE_HOOK_MACROS_H
