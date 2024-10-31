#include "../src/RuleSystem.h"
#include "../src/DiceTray.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;
using namespace osflib;

int main() {
	
	StatSheet pg;
	StatSheet goblin;
	StatSheet sword;
	StatSheet magicMissile;
	StatSheet shortbow;
	
	static const Id ID_STAT_BO = 100;
	static const Id ID_STAT_STR = 101;
	static const Id ID_STAT_DEX = 102;
	static const Id ID_STAT_AC = 103;
	static const Id ID_STAT_ATHLETICS = 104;
	static const Id ID_STAT_BASEDAMAGE = 105;
	static const Id ID_SUBSTAT_MIN = 106;
	static const Id ID_SUBSTAT_MAX = 107;
	static const Id ID_SUBSTAT_BONUS = 108;
	static const Id ID_STAT_PHYSICALDAMAGE = 109;
	static const Id ID_STAT_RESISTANCE = 110;
	static const Id ID_STAT_HP = 111;
	static const Id ID_SUBSTAT_CURRENT = 112;
	
	pg.AddStat({ID_STAT_BO, 0, 1});
	pg.AddStat({ID_STAT_STR, 0, 1});
	pg.AddStat({ID_STAT_DEX, 0, -2});
	pg.AddStat({ID_STAT_AC, 0, 15});
	pg.AddStat({ID_STAT_ATHLETICS, 0, 3});
	pg.AddStat({ID_STAT_HP, ID_SUBSTAT_CURRENT, 7});
	pg.AddStat({ID_STAT_HP, ID_SUBSTAT_MAX, 7});
	
	goblin.AddStat({ID_STAT_BO, 0, 0});
	goblin.AddStat({ID_STAT_STR, 0, 0});
	goblin.AddStat({ID_STAT_DEX, 0, 0});
	goblin.AddStat({ID_STAT_AC, 0, 14});
	
	sword.AddStat({ID_STAT_BASEDAMAGE, ID_SUBSTAT_MIN, 1});
	sword.AddStat({ID_STAT_BASEDAMAGE, ID_SUBSTAT_MAX, 8});
	sword.AddStat({ID_STAT_BASEDAMAGE, ID_SUBSTAT_BONUS, 0});
	
	shortbow.AddStat({ID_STAT_BASEDAMAGE, ID_SUBSTAT_MIN, 1});
	shortbow.AddStat({ID_STAT_BASEDAMAGE, ID_SUBSTAT_MAX, 6});
	shortbow.AddStat({ID_STAT_BASEDAMAGE, ID_SUBSTAT_BONUS, 0});
	
	magicMissile.AddStat({ID_STAT_BASEDAMAGE, ID_SUBSTAT_MIN, 1});
	magicMissile.AddStat({ID_STAT_BASEDAMAGE, ID_SUBSTAT_MAX, 4});
	magicMissile.AddStat({ID_STAT_BASEDAMAGE, ID_SUBSTAT_BONUS, 1});
	
	class Somed20RuleSystem : public RuleSystem {
	public:
		Somed20RuleSystem(){}
		~Somed20RuleSystem(){}
		
		bool ToHitMelee(const StatSheet& attacker, const StatSheet& defender, std::array<int, 2>& rolls) override {
			DiceTray tray;
			int bo = attacker.GetStat(ID_STAT_BO).GetValue();
			int str = attacker.GetStat(ID_STAT_STR).GetValue();
			int ac = defender.GetStat(ID_STAT_AC).GetValue();
			rolls[0] = tray.Roll(1, 20);
			rolls[1] = rolls[0] + bo + str;
			return rolls[1] >= ac;
		}
		
		bool ToHitRanged(const StatSheet& attacker, const StatSheet& defender, int distance, std::array<int, 2>& rolls) override {
			DiceTray tray;
			int bo = attacker.GetStat(ID_STAT_BO).GetValue();
			int dex = attacker.GetStat(ID_STAT_DEX).GetValue();
			int ac = defender.GetStat(ID_STAT_AC).GetValue();
			
			// in a real world implementation it will need some kind of access to a Table with
			// bonus/malus for the distance/weapon used... for simplicity this test omit this aspect
			
			rolls[0] = tray.Roll(1, 20);
			rolls[1] = rolls[0] + bo + dex;
			return rolls[1] >= ac;
		}
		
		bool StatCheck(const StatSheet& actor, Id stat, int targetNumber, std::array<int, 2>& rolls) override {
			DiceTray tray;
			rolls[0] = tray.Roll(1, 20);
			rolls[1] = rolls[0] + actor.GetStat(stat).GetValue();
			return rolls[1] >= targetNumber;
		}
		
		int CalculateDamageMelee(const StatSheet& attacker, const StatSheet& weapon, const StatSheet& armor, std::array<int, 2>& rolls) override {
			DiceTray tray;
			rolls[0] = tray.Roll(weapon.GetStat(ID_STAT_BASEDAMAGE, ID_SUBSTAT_MIN).GetValue(), 
				weapon.GetStat(ID_STAT_BASEDAMAGE, ID_SUBSTAT_MAX).GetValue(), 
				weapon.GetStat(ID_STAT_BASEDAMAGE, ID_SUBSTAT_BONUS).GetValue());
			rolls[1] = rolls[0] + attacker.GetStat(ID_STAT_STR).GetValue();
			return rolls[1];
		}
		
		int CalculateDamageRanged(const StatSheet& attacker, const StatSheet& weapon, const StatSheet& armor, std::array<int, 2>& rolls) override {
			DiceTray tray;
			rolls[0] = tray.Roll(weapon.GetStat(ID_STAT_BASEDAMAGE, ID_SUBSTAT_MIN).GetValue(), 
				weapon.GetStat(ID_STAT_BASEDAMAGE, ID_SUBSTAT_MAX).GetValue(), 
				weapon.GetStat(ID_STAT_BASEDAMAGE, ID_SUBSTAT_BONUS).GetValue());
			rolls[1] = rolls[0];
			return rolls[1];
		}
		
		int CalculateDamageSpell(const StatSheet& attacker, const StatSheet& spell, const StatSheet& armor, std::array<int, 2>& rolls) override {
			DiceTray tray;
			rolls[0] = tray.Roll(spell.GetStat(ID_STAT_BASEDAMAGE, ID_SUBSTAT_MIN).GetValue(), 
				spell.GetStat(ID_STAT_BASEDAMAGE, ID_SUBSTAT_MAX).GetValue(), 
				spell.GetStat(ID_STAT_BASEDAMAGE, ID_SUBSTAT_BONUS).GetValue());
			rolls[1] = rolls[0];
			return rolls[1];
		}
		
		void DamageActor(StatSheet& actor, Id damageType, int damageAmount) override {
			int resistance = 0;
			if(actor.HasStat(ID_STAT_RESISTANCE, damageType)) {
				resistance = actor.GetStat(ID_STAT_RESISTANCE, damageType).GetValue();
			}
			int damage = damageAmount - resistance;
			if(damage < 0) damage = 0;
			actor.EditStat(ID_STAT_HP, ID_SUBSTAT_CURRENT).AddValue(damage * -1);
		}
		
		void HealActor(StatSheet& actor, int healAmount, bool completeHeal) override {
			int current = actor.GetStat(ID_STAT_HP, ID_SUBSTAT_CURRENT).GetValue();
			int max = actor.GetStat(ID_STAT_HP, ID_SUBSTAT_MAX).GetValue();
			if(completeHeal) current = max;
			else current += healAmount;
			if(current > max) current = max;
			actor.EditStat(ID_STAT_HP, ID_SUBSTAT_CURRENT).SetValue(current);
		}
	};
	
	//---
	
	cout << "Perform melee to hit rolls: " << endl;
	{
		
		Somed20RuleSystem system;
		std::array<int, 2> rolls;
		bool hit = system.ToHitMelee(pg, goblin, rolls);
		std::string result = hit ? "hit" : "miss";
		cout << "PG attacks Goblin: rolled " << rolls[0] << " + " << rolls[1] - rolls[0] << " vs AC " << goblin.GetStat(ID_STAT_AC).GetValue() << ": " << result << endl;
		
		hit = system.ToHitMelee(goblin, pg, rolls);
		result = hit ? "hit" : "miss";
		cout << "Goblin attacks Pg: rolled " << rolls[0] << " + " << rolls[1] - rolls[0] << " vs AC " << pg.GetStat(ID_STAT_AC).GetValue() << ": " << result << endl;
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Perform a ranged to hit roll: " << endl;
	{
		
		Somed20RuleSystem system;
		std::array<int, 2> rolls;
		bool hit = system.ToHitRanged(pg, goblin, 9, rolls);
		std::string result = hit ? "hit" : "miss";
		cout << "Rolled " << rolls[0] << " + " << rolls[1] - rolls[0] << " vs AC " << goblin.GetStat(ID_STAT_AC).GetValue() << ": " << result << endl;
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Perform a skill check: " << endl;
	{
		Somed20RuleSystem system;
		std::array<int, 2> rolls;
		bool check = system.StatCheck(pg, ID_STAT_ATHLETICS, 12, rolls);
		std::string result = check ? "passed" : "failed";
		cout << "Rolled " << rolls[0] << " + " << rolls[1] - rolls[0] << " vs CD 12: " << result << endl;
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Perform a melee (sword) damage roll: " << endl;
	{
		Somed20RuleSystem system;
		std::array<int, 2> rolls;
		int damage = system.CalculateDamageMelee(pg, sword, sword, rolls);
		cout << "Rolled " << rolls[0] << " + " << rolls[1] - rolls[0] << " total: " << damage << endl;
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Perform a ranged (shortbow) damage roll: " << endl;
	{
		Somed20RuleSystem system;
		std::array<int, 2> rolls;
		int damage = system.CalculateDamageRanged(pg, shortbow, shortbow, rolls);
		cout << "Rolled " << rolls[0] << " + " << rolls[1] - rolls[0] << " total: " << damage << endl;
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Perform a spell (magic missile) damage roll: " << endl;
	{
		Somed20RuleSystem system;
		std::array<int, 2> rolls;
		int damage = system.CalculateDamageSpell(pg, magicMissile, magicMissile, rolls);
		cout << "Rolled " << rolls[0] << " + " << rolls[1] - rolls[0] << " total: " << damage << endl;
	} 
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Damage actor: ";
	{
		Somed20RuleSystem system;
		assert(pg.GetStat(ID_STAT_HP, ID_SUBSTAT_CURRENT).GetValue() == 7);
		system.DamageActor(pg, ID_STAT_PHYSICALDAMAGE, 5);
		assert(pg.GetStat(ID_STAT_HP, ID_SUBSTAT_CURRENT).GetValue() == 2);
	} 
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Heal actor: ";
	{
		Somed20RuleSystem system;
		pg.EditStat(ID_STAT_HP, ID_SUBSTAT_MAX).SetValue(7);
		pg.EditStat(ID_STAT_HP, ID_SUBSTAT_CURRENT).SetValue(2);
		system.HealActor(pg, 10, false);
		assert(pg.GetStat(ID_STAT_HP, ID_SUBSTAT_CURRENT).GetValue() == 7);
		pg.EditStat(ID_STAT_HP, ID_SUBSTAT_CURRENT).SetValue(2);
		system.HealActor(pg, 3, false);
		assert(pg.GetStat(ID_STAT_HP, ID_SUBSTAT_CURRENT).GetValue() == 5);
		system.HealActor(pg, 0, true);
		assert(pg.GetStat(ID_STAT_HP, ID_SUBSTAT_CURRENT).GetValue() == 7);
	} 
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << endl << "All tests passed with success!" << endl;
	
	return 0;
}