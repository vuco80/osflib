#include "../src/Table.h"
#include "../src/DiceTray.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;
using namespace osflib;

int main() {
	
	cout << "Set Fighter Level Progression Table: ";
	{
		struct ProgressionLevel {
			int level;
			int xp;
		};
		Id FIGHTER_XP_TABLE = 100;
		Table<ProgressionLevel> fighterXPTable(FIGHTER_XP_TABLE, 3);
		Results r = fighterXPTable.AddRow({1, 0});
		assert(r == Success);
		fighterXPTable.AddRow({2, 2000});
		fighterXPTable.AddRow({3, 4000});
	}
	cout << "SUCCESS" << endl;
	
	// ---
	
	cout << "Search fighter xp need for level 3: ";
	{
		struct ProgressionLevel {
			int level;
			int xp;
		};
		Id FIGHTER_XP_TABLE = 100;
		Table<ProgressionLevel> fighterXPTable(FIGHTER_XP_TABLE, 3);
		fighterXPTable.AddRow({1, 0});
		fighterXPTable.AddRow({2, 2000});
		fighterXPTable.AddRow({3, 4000});
		
		class XpQuery : public TableQuery<ProgressionLevel> {
		public:
			void SetLevel(int level) { m_Level = level; }
			void Select(const ProgressionLevel& row) override {
				if(row.level == m_Level) m_Rows.push_back(row);
			}
		private:
			int m_Level;
		};
		XpQuery query;
		query.SetLevel(3);
		fighterXPTable.Query(query);
		assert(query.Rows().size() == 1);
		assert(query.Rows()[0].xp == 4000);
		cout << query.Rows()[0].xp << " ";
	}
	cout << "SUCCESS" << endl;
	
	// ---
	
	cout << "Select a random encounter (x10): ";
	{
		struct Encounter {
			Id monster;
			int maxQty;
		};
		Id GOBLIN = 100;
		Id ORC = 101;
		Id ENCOUNTER_TABLE = 200;
		Table<Encounter> encounterTable(ENCOUNTER_TABLE, 10);
		encounterTable.AddRow({GOBLIN, 4});
		encounterTable.AddRow({GOBLIN, 6});
		encounterTable.AddRow({GOBLIN, 3});
		encounterTable.AddRow({GOBLIN, 8});
		encounterTable.AddRow({GOBLIN, 10});
		encounterTable.AddRow({GOBLIN, 12});
		encounterTable.AddRow({ORC, 1});
		encounterTable.AddRow({ORC, 4});
		encounterTable.AddRow({ORC, 6});
		encounterTable.AddRow({ORC, 8});
		DiceTray tray;
		for(int i=0; i<10; ++i) {
			const Encounter& enc = encounterTable.Random();
			assert(enc.monster == GOBLIN || enc.monster == ORC);
			string monster = enc.monster == GOBLIN ? " Goblins" : " Orcs";
			cout << (i+1) << ") 1d" << enc.maxQty << " " << monster << " -> " << tray.Roll(1, enc.maxQty) << monster << endl; 
		}
	}
	cout << "SUCCESS" << endl;
	
	return 0;
}