#ifndef OSFLIB_TABLE_H
#define OSFLIB_TABLE_H

#include "Base.h"
#include <vector>
#include <cstdlib>

namespace osflib {
	
	template<typename T>
	class TableQuery {
	public:
		TableQuery(){}
		virtual ~TableQuery(){}
		
		virtual void Select(const T& row) = 0;
		const std::vector<T>& Rows(){ return m_Rows; }
		
	protected:
		std::vector<T> m_Rows;
	};
	
	template<typename T>
	class Table : public ResourceBase {
	public:
		Table(Id id, unsigned int rowCount) : ResourceBase(id), m_Index(0) {
			m_Rows.reserve(rowCount);
		}
		~Table() {}
		
		Results AddRow(T row) {
			if(m_Index >= m_Rows.capacity()) return OutOfBounds;
			m_Rows[m_Index] = row;
			m_Index++;
			return Success;
		}
		
		const T& Random() {
			int randomIndex = rand() % m_Rows.capacity();
			return m_Rows[randomIndex]; 
		}
		
		void Query(TableQuery<T>& query) {
			for(int i=0; i<m_Rows.capacity(); ++i) query.Select(m_Rows[i]);
		}
		
	private:
		unsigned int m_Index;
		std::vector<T> m_Rows;
	};	
}

#endif