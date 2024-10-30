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
	
	static const Id ID_STAT_BO = 100;
	static const Id ID_STAT_STR = 101;
	static const Id ID_STAT_DEX = 102;
	static const Id ID_STAT_AC = 103;
	static const Id ID_STAT_ATHLETICS = 104;
	
	
	pg.AddStat({ID_STAT_BO, 0, 1});
	pg.AddStat({ID_STAT_STR, 0, 1});
	pg.AddStat({ID_STAT_DEX, 0, -2});
	pg.AddStat({ID_STAT_AC, 0, 15});
	pg.AddStat({ID_STAT_ATHLETICS, 0, 3});
	
	goblin.AddStat({ID_STAT_BO, 0, 0});
	goblin.AddStat({ID_STAT_STR, 0, 0});
	goblin.AddStat({ID_STAT_DEX, 0, 0});
	goblin.AddStat({ID_STAT_AC, 0, 14});
	
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
	
	cout << endl << "All tests passed with success!" << endl;
	
	return 0;
}