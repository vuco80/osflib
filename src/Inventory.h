#ifndef OSFLIB_INVENTORY_H
#define OSFLIB_INVENTORY_H

#include "Base.h"
#include <forward_list>

namespace osflib {
	
	struct InventoryEntry {
		Id element;
		unsigned int quantity;
		
		InventoryEntry(Id element, unsigned int quantity) : element(element), quantity(quantity) {}
		bool operator==(const InventoryEntry& other) { return element == other.element; }
	};
	
	typedef std::forward_list<InventoryEntry>::iterator EntryForwardIterator;
	
	class Inventory : public ResourceBase {
	public:
		Inventory(Id id);
		~Inventory();
		
		void AddEntry(const InventoryEntry& entry);
		Results RemoveEntry(const InventoryEntry& entry);
		Results MoveEntry(const InventoryEntry& entry, Inventory* destination);
		Results GetEntry(Id entryId, InventoryEntry* destination);
		void Visit(Visitor<InventoryEntry>& visitor);
		void Clear();
		unsigned int Size() const;
		
	private:
		
		Results Find(const InventoryEntry& entry, EntryForwardIterator& iter);
		Results Find(Id entryId, EntryForwardIterator& iter);
	
		std::forward_list<InventoryEntry> m_Entries;
		unsigned int m_Size;
	};	
}

#endif