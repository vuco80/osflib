#ifndef OSFLIB_BFRPG_TABLES_H
#define OSFLIB_BFRPG_TABLES_H

#include "../../Defines.h"
#include "../../Table.h"
#include "Defines.h"

namespace osflib { namespace bfrpg {
	
	struct StatModifier {
		int statValue;
		int modifier;
	};
	
	class QueryStatModifier : public TableQuery<StatModifier> {
	public:
		void Search(int score) { m_Score = score; }
		void Select(const StatModifier& row) override {
			if(row.statValue == m_Score) m_Rows.push_back(row);
		}
	private:
		int m_Score;
	};
	
	class BFTables {
	public:
		BFTables() : m_StatModifierTable(TABLE_ID_STATMODIFIER, 15) {
			m_StatModifierTable.AddRow({3, -3});
			m_StatModifierTable.AddRow({4, -2});
			m_StatModifierTable.AddRow({5, -2});
			m_StatModifierTable.AddRow({6, -1});
			m_StatModifierTable.AddRow({7, -1});
			m_StatModifierTable.AddRow({8, -1});
			m_StatModifierTable.AddRow({9, 0});
			m_StatModifierTable.AddRow({10, 0});
			m_StatModifierTable.AddRow({11, 0});
			m_StatModifierTable.AddRow({12, 0});
			m_StatModifierTable.AddRow({13, 1});
			m_StatModifierTable.AddRow({14, 1});
			m_StatModifierTable.AddRow({15, 1});
			m_StatModifierTable.AddRow({16, 2});
			m_StatModifierTable.AddRow({17, 2});
			m_StatModifierTable.AddRow({18, 3});
		}
		
		const QueryStatModifier& QueryStatModifierTable(int score) {
			m_StatModifierQuery.Search(score);
			m_StatModifierTable.Query(m_StatModifierQuery);
			return m_StatModifierQuery;
		}
		
	private:
		QueryStatModifier m_StatModifierQuery;
		Table<StatModifier> m_StatModifierTable;
	};

} }

#endif