#ifndef OSFLIB_DICETRAY_H
#define OSFLIB_DICETRAY_H

namespace osflib {
	
	class DiceTray {
	public:
		DiceTray();
		~DiceTray();
		
		/* \brief Sets the minimum roll value, i.e: if a roll cannot go negative, or 0. 
		* default: 1
		*/
		void SetMinRollValue(int value);
		
		/* \brief Rolls diceCount dice of dieFaces faces, applying the modifier to each roll.
		* A roll result cannot go under 0.
		*/
		int Roll(int diceCount, int dieFaces, int modifier = 0);
		
		/* \brief Same as Roll, but all the single rolls are stored in the results array */
		int Roll(int diceCount, int dieFaces, int* results, int modifier = 0);
		
	private:
	
		int RollDie(int dieFaces, int modifier);
		
		int m_MinValue;
	};
	
}

#endif