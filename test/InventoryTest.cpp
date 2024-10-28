#include "../src/Inventory.h"
#include <iostream>
#include <cassert>

using namespace std;
using namespace osflib;

int main() {
	cout << "Creating empty Inventory: ";
	{
		Inventory test(100);
		assert(test.Size() == 0);
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Add 1 element: ";
	{
		Inventory test(100);
		Id SWORD = 200;
		test.AddEntry({SWORD, 1});
		assert(test.Size() == 1);
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Add 1 element stacked: ";
	{
		Inventory test(100);
		Id SWORD = 200;
		test.AddEntry({SWORD, 2});
		assert(test.Size() == 1);
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Move 1 element: ";
	{
		Inventory test(100), receiver(101);
		Id SWORD = 200;
		test.AddEntry({SWORD, 1});
		Results res = test.MoveEntry({SWORD, 1}, &receiver);
		assert(res == Success);
		assert(test.Size() == 0);
		assert(receiver.Size() == 1);
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Remove too much quantity: ";
	{
		Inventory test(100);
		Id SWORD = 200;
		test.AddEntry({SWORD, 1});
		Results res = test.RemoveEntry({SWORD, 2});
		assert(res == QuantityOverflow);
		assert(test.Size() == 1);
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Get entry: ";
	{
		Inventory test(100);
		InventoryEntry entry(0,0);
		Id SWORD = 200;
		test.AddEntry({SWORD, 5});
		test.AddEntry({SWORD, 1});
		Results res = test.GetEntry(SWORD, &entry);
		assert(res == Success);
		assert(entry.quantity == 6);
	}
	cout << "SUCCESS" << endl;
	
	//---
	
	cout << "Visitor entry: ";
	{
		Inventory test(100);
		InventoryEntry entry(0,0);
		Id SWORD = 200;
		Id DAGGER = 201;
		class PrintInvVisitor : public Visitor<InventoryEntry> {
		public:
			PrintInvVisitor() : Visitor<InventoryEntry>(){}
			~PrintInvVisitor() {}
			void Visit(const InventoryEntry& entry) override {
				cout << entry.element << " qta: " << entry.quantity << endl;
			}
		};
		PrintInvVisitor visitor;
		test.AddEntry({SWORD, 1});
		test.AddEntry({DAGGER, 2});
		test.Visit(visitor);
	}
	cout << "SUCCESS" << endl;
	
	cout << endl << "All tests passed with success!" << endl;
	
	return 0;
}