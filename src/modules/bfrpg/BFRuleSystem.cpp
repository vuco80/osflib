#include "Defines.h"
#include "BFRuleSystem.h"
#include "BFTables.h"

namespace osflib { namespace bfrpg {
	
	static BFTables bfTables;
	
	BFRuleSystem::BFRuleSystem() { }
	BFRuleSystem::~BFRuleSystem() { }
	
	bool BFRuleSystem::ToHitMelee(const StatSheet& attacker, const StatSheet& defender, std::array<int, 2>& rolls) {
		int bo = attacker.GetStat(STAT_ID_BO).GetValue();
		int str = attacker.GetStat(STAT_ID_STRENGTH).GetValue();
		int modifier = bfTables.QueryStatModifierTable(str).Rows()[0].modifier;
		int ac = defender.GetStat(STAT_ID_AC).GetValue();
		int roll = m_Tray.Roll(1, 20);
		int total = roll + bo + modifier;
		rolls[0] = roll;
		rolls[1] = total;
		return total >= ac;
	}
	
	bool BFRuleSystem::ToHitRanged(const StatSheet& attacker, const StatSheet& defender, int distance, std::array<int, 2>& roll) {
		return false;
	}
	
	bool BFRuleSystem::StatCheck(const StatSheet& actor, Id stat, int targetNumber, std::array<int, 2>& roll) {
		return false;
	}
	
	int BFRuleSystem::CalculateDamageMelee(const StatSheet& attacker, const StatSheet& weapon, const StatSheet& armor, std::array<int, 2>& rolls) {
		return 0;
	}
	
	int BFRuleSystem::CalculateDamageRanged(const StatSheet& attacker, const StatSheet& weapon, const StatSheet& armor, std::array<int, 2>& rolls) {
		return 0;
	}
	
	int BFRuleSystem::CalculateDamageSpell(const StatSheet& attacker, const StatSheet& spell, const StatSheet& armor, std::array<int, 2>& rolls) {
		return 0;
	}
	
	void BFRuleSystem::DamageActor(StatSheet& actor, Id damageType, int damageAmount) {
		
	}
	
	void BFRuleSystem::HealActor(StatSheet& actor, int healAmount, bool completeHeal) {
		
	}

} }