@echo off
g++ -c -o dicetray.o ../src/DiceTray.cpp
g++ -c -o inventory.o ../src/Inventory.cpp
ar rcs -o libosflib.a dicetray.o inventory.o