#include "DiceTray.h"
#include <cstdlib>

namespace osflib {

	DiceTray::DiceTray() : m_MinValue(1) {
	}
	
	DiceTray::~DiceTray() {
	}

	int DiceTray::Roll(int diceCount, int dieFaces, int modifier) {
		int result = 0;
		for(int i=0; i<diceCount; ++i) {
			result += RollDie(dieFaces, modifier);
		}
		return result;
	}
	
	int DiceTray::Roll(int diceCount, int dieFaces, int* results, int modifier) {
		int result = 0;
		for(int i=0; i<diceCount; ++i) {
			int roll = RollDie(dieFaces, modifier);
			results[i] = roll;
			result += roll;
		}
		return result;
	}
	
	int DiceTray::RollDie(int dieFaces, int modifier) {
		int roll = 1 + (rand() % dieFaces) + modifier;
		if(roll < m_MinValue) roll = m_MinValue;
		return roll;
	}
}