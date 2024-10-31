#ifndef OSFLIB_BFRPG_RULESYSTEM_H
#define OSFLIB_BFRPG_RULESYSTEM_H

#include "../../Defines.h"
#include "../../RuleSystem.h"
#include "../../DiceTray.h"

namespace osflib { namespace bfrpg {
	
	class BFRuleSystem : public osflib::RuleSystem {
	public:
		BFRuleSystem();
		~BFRuleSystem();
		bool ToHitMelee(const StatSheet& attacker, const StatSheet& defender, std::array<int, 2>& roll) override;
		bool ToHitRanged(const StatSheet& attacker, const StatSheet& defender, int distance, std::array<int, 2>& roll) override;
		bool StatCheck(const StatSheet& actor, Id stat, int targetNumber, std::array<int, 2>& roll) override;
		int CalculateDamageMelee(const StatSheet& attacker, const StatSheet& weapon, const StatSheet& armor, std::array<int, 2>& rolls) override;
		int CalculateDamageRanged(const StatSheet& attacker, const StatSheet& weapon, const StatSheet& armor, std::array<int, 2>& rolls) override;
		int CalculateDamageSpell(const StatSheet& attacker, const StatSheet& spell, const StatSheet& armor, std::array<int, 2>& rolls) override;
		void DamageActor(StatSheet& actor, Id damageType, int damageAmount) override;
		void HealActor(StatSheet& actor, int healAmount, bool completeHeal) override;
		
	private:
		osflib::DiceTray m_Tray;
	};

} }

#endif