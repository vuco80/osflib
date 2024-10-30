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
	};

}

#endif