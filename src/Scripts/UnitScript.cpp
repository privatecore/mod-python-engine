#include "HookMacros.h"
#include "ScriptMgr.h"
#include "Player.h"

class PythonUnitScript : public UnitScript
{
public:
    PythonUnitScript() : UnitScript("PythonUnitScript") {}

    // Called when a unit deals healing to another unit
    void OnHeal(Unit* healer, Unit* reciever, uint32& gain) { TRIGGER_UNIT_HOOK(ON_HEAL, healer, reciever, gain); }

    // Called when a unit deals damage to another unit
    void OnDamage(Unit* attacker, Unit* victim, uint32& damage)
    {
        TRIGGER_UNIT_HOOK(ON_DAMAGE, attacker, victim, damage);
    }

    // Called when DoT's Tick Damage is being Dealt
    // Attacker can be nullptr if he is despawned while the aura still exists on target
    void ModifyPeriodicDamageAurasTick(Unit* target, Unit* attacker, uint32& damage, SpellInfo const* spellInfo)
    {
        TRIGGER_UNIT_HOOK(MODIFY_PERIODIC_DAMAGE_AURAS_TICK, target, attacker, damage, spellInfo);
    }

    // Called when Melee Damage is being Dealt
    void ModifyMeleeDamage(Unit* target, Unit* attacker, uint32& damage)
    {
        TRIGGER_UNIT_HOOK(MODIFY_MELEE_DAMAGE, target, attacker, std::ref(damage));
    }

    // Called when Spell Damage is being Dealt
    void ModifySpellDamageTaken(Unit* target, Unit* attacker, int32& damage, SpellInfo const* spellInfo)
    {
        TRIGGER_UNIT_HOOK(MODIFY_SPELL_DAMAGE_TAKEN, target, attacker, std::ref(damage), spellInfo);
    }

    // Called when Heal is Recieved
    void ModifyHealReceived(Unit* target, Unit* healer, uint32& addHealth, SpellInfo const* spellInfo)
    {
        TRIGGER_UNIT_HOOK(MODIFY_HEAL_RECEIVED, target, healer, std::ref(addHealth), spellInfo);
    }

    void OnBeforeRollMeleeOutcomeAgainst(Unit const* attacker, Unit const* victim, WeaponAttackType attType,
                                         int32& attackerMaxSkillValueForLevel, int32& victimMaxSkillValueForLevel,
                                         int32& attackerWeaponSkill, int32& victimDefenseSkill, int32& crit_chance,
                                         int32& miss_chance, int32& dodge_chance, int32& parry_chance,
                                         int32& block_chance)
    {
        TRIGGER_UNIT_HOOK(ON_BEFORE_ROLL_MELEE_OUTCOME_AGAINST, attacker, victim, attType,
                          std::ref(attackerMaxSkillValueForLevel), std::ref(victimMaxSkillValueForLevel),
                          std::ref(attackerWeaponSkill), std::ref(victimDefenseSkill), std::ref(crit_chance),
                          std::ref(miss_chance), std::ref(dodge_chance), std::ref(parry_chance),
                          std::ref(block_chance));
    }

    void OnAuraApply(Unit* unit, Aura* aura) { TRIGGER_UNIT_HOOK(ON_AURA_APPLY, unit, aura); }

    void OnAuraRemove(Unit* unit, AuraApplication* aurApp, AuraRemoveMode mode)
    {
        TRIGGER_UNIT_HOOK(ON_AURA_REMOVE, unit, aurApp, mode);
    }

    bool IfNormalReaction(Unit const* unit, Unit const* target, ReputationRank& repRank)
    {
        TRIGGER_UNIT_HOOK(IF_NORMAL_REACTION, unit, target, std::ref(repRank));
        return true;
    }

    bool CanSetPhaseMask(Unit const* unit, uint32 newPhaseMask, bool update)
    {
        TRIGGER_UNIT_HOOK(CAN_SET_PHASE_MASK, unit, newPhaseMask, update);
        return false;
    }

    bool IsCustomBuildValuesUpdate(Unit const* unit, uint8 updateType, ByteBuffer& fieldBuffer, Player const* target,
                                   uint16 index)
    {
        TRIGGER_UNIT_HOOK(IS_CUSTOM_BUILD_VALUES_UPDATE, unit, updateType, std::ref(fieldBuffer), target, index);
        return false;
    }

    bool ShouldTrackValuesUpdatePosByIndex(Unit const* unit, uint8 updateType, uint16 index)
    {
        TRIGGER_UNIT_HOOK(SHOULD_TRACK_VALUES_UPDATE_POS_BY_INDEX, unit, updateType, index);
        return false;
    }

    void OnPatchValuesUpdate(Unit const* unit, ByteBuffer& valuesUpdateBuf, BuildValuesCachePosPointers& posPointers,
                             Player* target)
    {
        TRIGGER_UNIT_HOOK(ON_PATCH_VALUES_UPDATE, unit, std::ref(valuesUpdateBuf), std::ref(posPointers), target);
    }

    void OnUnitUpdate(Unit* unit, uint32 diff) { TRIGGER_UNIT_HOOK(ON_UNIT_UPDATE, unit, diff); }

    void OnDisplayIdChange(Unit* unit, uint32 displayId) { TRIGGER_UNIT_HOOK(ON_DISPLAYID_CHANGE, unit, displayId); }

    void OnUnitEnterEvadeMode(Unit* unit, uint8 why) { TRIGGER_UNIT_HOOK(ON_UNIT_ENTER_EVADE_MODE, unit, why); }

    void OnUnitEnterCombat(Unit* unit, Unit* victim) { TRIGGER_UNIT_HOOK(ON_UNIT_ENTER_COMBAT, unit, victim); }

    void OnUnitDeath(Unit* unit, Unit* killer) { TRIGGER_UNIT_HOOK(ON_UNIT_DEATH, unit, killer); }

    void OnUnitSetShapeshiftForm(Unit* unit, uint8 form) { TRIGGER_UNIT_HOOK(ON_UNIT_SET_SHAPESHIFT_FORM, unit, form); }
};

void AddSC_PythonUnitScripts()
{
    new PythonUnitScript();
}
