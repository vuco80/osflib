@echo off
g++ -c -o dicetray.o ../src/DiceTray.cpp
g++ -c -o inventory.o ../src/Inventory.cpp
g++ -c -o table.o ../src/Table.cpp
g++ -c -o statsheet.o ../src/StatSheet.cpp
g++ -c -o module.o ../src/modules/ModuleCompile.cpp -DOSFLIB_MODULE_BFRPG
ar rcs -o libosflib.a dicetray.o inventory.o table.o statsheet.o module.o