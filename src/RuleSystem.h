#ifndef OSFLIB_RULESYSTEM_H
#define OSFLIB_RULESYSTEM_H

#include "StatSheet.h"
#include "Table.h"

#include <array>

namespace osflib {

	class RuleSystem {
	public:
		RuleSystem(){}
		virtual ~RuleSystem() {}
		
		virtual bool ToHitMelee(const StatSheet& attacker, const StatSheet& defender, std::array<int, 2>& roll) = 0;
		virtual bool ToHitRanged(const StatSheet& attacker, const StatSheet& defender, int distance, std::array<int, 2>& roll) = 0;
		virtual bool StatCheck(const StatSheet& actor, Id stat, int targetNumber, std::array<int, 2>& roll) = 0;
		virtual int CalculateDamageMelee(const StatSheet& attacker, const StatSheet& weapon, const StatSheet& armor, std::array<int, 2>& rolls) = 0;
		virtual int CalculateDamageRanged(const StatSheet& attacker, const StatSheet& weapon, const StatSheet& armor, std::array<int, 2>& rolls) = 0;
		virtual int CalculateDamageSpell(const StatSheet& attacker, const StatSheet& spell, const StatSheet& armor, std::array<int, 2>& rolls) = 0;
		virtual void DamageActor(StatSheet& actor, Id damageType, int damageAmount) = 0;
		virtual void HealActor(StatSheet& actor, int healAmount, bool completeHeal) = 0;
	};

}

#endif