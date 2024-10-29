#ifndef OSFLIB_STAT_H
#define OSFLIB_STAT_H

#include <map>
#include <forward_list>
#include "Defines.h"

namespace osflib {

	class Stat {
	public:
		Stat() {}
		Stat(Id id, Id subId, int value) : m_Id(id), m_SubId(subId), m_Value(value) {}
		Stat(const Stat& other) : m_Id(other.GetId()), m_SubId(other.GetSubId()), m_Value(other.GetValue()) {}
		~Stat() {}
		
		Id GetId() const { return m_Id; }
		Id GetSubId() const { return m_SubId; }
		int GetValue() const { return m_Value; }
		
		bool operator==(const Stat& other) { return m_Id == other.m_Id && m_SubId == other.m_SubId; }
		
	private:
		Id m_Id;
		Id m_SubId;
		int m_Value;
	};
	
	// ---
	
	class StatSheet {
	public:
		StatSheet();
		~StatSheet();
		
		void AddStat(const Stat& stat);
		const Stat& GetStat(Id statId);
		const Stat& GetStat(Id statId, Id statSubId);
		
	private:
		std::map<Id, Stat> m_Stats;
		std::forward_list<Stat> m_SubIdStats;
	};
}

#endif