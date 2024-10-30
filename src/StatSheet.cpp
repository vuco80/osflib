#include "StatSheet.h"
#include <algorithm>

namespace osflib {

	StatSheet::StatSheet() {
	}
	
	StatSheet::~StatSheet() {
	}
		
	void StatSheet::AddStat(const Stat& stat) {
		if(stat.GetSubId() != EmptyId) {
			std::forward_list<Stat>::iterator iter = std::find(m_SubIdStats.begin(), m_SubIdStats.end(), stat);
			if(iter == m_SubIdStats.end()) m_SubIdStats.push_front(stat);
		}
		else {
			std::map<Id, Stat>::iterator iter = m_Stats.find(stat.GetId());
			if(iter == m_Stats.end()) m_Stats[stat.GetId()] = Stat(stat);
		}
	}
	
	const Stat& StatSheet::GetStat(Id statId) const {
		return m_Stats.at(statId);
	}
	
	const Stat& StatSheet::GetStat(Id statId, Id statSubId) const {
		Stat search(statId, statSubId, 0);
		std::forward_list<Stat>::const_iterator iter = std::find(m_SubIdStats.begin(), m_SubIdStats.end(), search);
		return (*iter);
	}

}