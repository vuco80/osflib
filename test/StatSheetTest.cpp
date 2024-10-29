#include "../src/StatSheet.h"
#include "../src/DiceTray.h"
#include <iostream>
#include <cassert>

using namespace std;
using namespace osflib;

int main() {
	
	cout << "Creating a basic fantasy stat block: " << endl;
	{
		DiceTray tray;
		Id STR = 100;
		Id INT = 101;
		Id WIS = 102;
		Id DEX = 103;
		Id COS = 104;
		Id CHA = 105;
		StatSheet sheet;
		sheet.AddStat({ STR, 0, tray.Roll(3, 6) });
		sheet.AddStat({ INT, 0, tray.Roll(3, 6) });
		sheet.AddStat({ WIS, 0, tray.Roll(3, 6) });
		sheet.AddStat({ DEX, 0, tray.Roll(3, 6) });
		sheet.AddStat({ COS, 0, tray.Roll(3, 6) });
		sheet.AddStat({ CHA, 0, tray.Roll(3, 6) });
		cout << "STR: " << sheet.GetStat(STR).GetValue() << endl;
		cout << "INT: " << sheet.GetStat(INT).GetValue() << endl;
		cout << "WIS: " << sheet.GetStat(WIS).GetValue() << endl;
		cout << "DEX: " << sheet.GetStat(DEX).GetValue() << endl;
		cout << "COS: " << sheet.GetStat(COS).GetValue() << endl;
		cout << "CHA: " << sheet.GetStat(CHA).GetValue() << endl;
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Using subid stat (multiclass character): " << endl;
	{
		Id LEVEL = 100;
		Id CLASS_FIGHTER = 101;
		Id CLASS_WIZARD = 102;
		StatSheet sheet;
		sheet.AddStat({ LEVEL, CLASS_FIGHTER, 2 });
		sheet.AddStat({ LEVEL, CLASS_WIZARD, 1 });
		assert(sheet.GetStat(LEVEL, CLASS_FIGHTER).GetValue() == 2);
		assert(sheet.GetStat(LEVEL, CLASS_WIZARD).GetValue() == 1);
		cout << "Level " << sheet.GetStat(LEVEL, CLASS_FIGHTER).GetValue() << " fighter / " << sheet.GetStat(LEVEL, CLASS_WIZARD).GetValue() << " wizard" << endl;
	}
	cout << "SUCCESS" << endl;
	
	cout << endl << "All tests passed with success!" << endl;
	
	return 0;
}