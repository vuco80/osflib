@echo off
g++ DiceTrayTest.cpp -o DiceTrayTest.exe -losflib -L"../build/"
g++ InventoryTest.cpp -o InventoryTest.exe -losflib -L"../build/"