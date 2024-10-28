#include "Inventory.h"
#include <algorithm>

namespace osflib {

	Inventory::Inventory(Id id) : ResourceBase(id), m_Size(0) {
	}
	
	Inventory::~Inventory() {
		
	}
	
	void Inventory::AddEntry(const InventoryEntry& entry) {
		EntryForwardIterator iter;
		Results res = Find(entry, iter);
		if(res == NotFound) {
			m_Entries.push_front(entry);
			m_Size += 1;
		}
		else (*iter).quantity += entry.quantity;
	}
	
	Results Inventory::RemoveEntry(const InventoryEntry& entry) {
		EntryForwardIterator iter;
		Results res = Find(entry, iter);
		if(res != Success) return res;
		
		if((*iter).quantity < entry.quantity) return QuantityOverflow;
		(*iter).quantity -= entry.quantity;
		if((*iter).quantity == 0) {
			m_Entries.remove(entry);
			m_Size -= 1;
		}
		return Success;
	}
	
	Results Inventory::MoveEntry(const InventoryEntry& entry, Inventory* destination) {
		EntryForwardIterator iter;
		Results res = Find(entry, iter);
		if(res != Success) return res;
		
		res = RemoveEntry(entry);
		
		if(res == Success) {
			destination->AddEntry(entry);
		}
		
		return Success;
	}
	
	Results Inventory::Find(const InventoryEntry& entry, EntryForwardIterator& iter) {
		iter = std::find(m_Entries.begin(), m_Entries.end(), entry);
		if(iter == m_Entries.end()) return NotFound;
		return Success;
	}
	
	Results Inventory::Find(Id entryId, EntryForwardIterator& iter) {
		InventoryEntry entry = {entryId, 0};
		return Find(entry, iter);
	}
	
	void Inventory::Clear() {
		m_Entries.clear();
	}
	
	unsigned int Inventory::Size() const {
		return m_Size;
	}
	
	Results Inventory::GetEntry(Id entryId, InventoryEntry* destination) {
		EntryForwardIterator iter;
		Results res = Find(entryId, iter);
		if(res != Success) return res;
		destination->element = (*iter).element;
		destination->quantity = (*iter).quantity;
		return Success;
	}
	
	void Inventory::Visit(Visitor<InventoryEntry>& visitor) {
		//for_each(m_Entries.begin(), m_Entries.end(), [visitor](const InventoryEntry& e) { visitor.Visit(e); });
		for(auto iter=m_Entries.begin(); iter != m_Entries.end(); ++iter) visitor.Visit((*iter));
	}
}