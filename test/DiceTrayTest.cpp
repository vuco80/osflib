#include "../src/DiceTray.h"
#include <iostream>
#include <cassert>

using namespace std;
using namespace osflib;

int main() {
	DiceTray tray;
	
	cout << "Rolling 100 times 1d8: ";
	for(int i=0; i<100; ++i) {
		int result = tray.Roll(1, 8);
		assert(result > 0 && result <= 8);
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Rolling 100 times 3d6: ";
	for(int i=0; i<100; ++i) {
		int result = tray.Roll(3, 6);
		assert(result >= 3 && result <= 18);
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Rolling 100 times 1d6-4 (no negative or 0 values): ";
	for(int i=0; i<100; ++i) {
		int result = tray.Roll(1, 6, -4);
		assert(result >= 1 && result <= 2);
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Rolling 1d20 with advantage and get 2 values: ";
	{
		int rolls[2];
		int result = tray.Roll(2, 20, rolls);
		assert(rolls[0] >= 1 && rolls[0] <= 20);
		assert(rolls[1] >= 1 && rolls[1] <= 20);
	}
	cout << "SUCCESS" << endl;
	
	cout << endl << "All tests passed with success!" << endl;
	
	return 0;
}