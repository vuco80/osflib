@echo off
g++ DiceTrayTest.cpp -o DiceTrayTest.exe -losflib -L"../build/"
g++ InventoryTest.cpp -o InventoryTest.exe -losflib -L"../build/"
g++ TableTest.cpp -o TableTest.exe -losflib -L"../build/"
g++ StatSheetTest.cpp -o StatSheetTest.exe -losflib -L"../build/"
g++ RuleSystemTest.cpp -o RuleSystemTest.exe -losflib -L"../build/"