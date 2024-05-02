# python3 src/cpp/util_write.py --left data/cones/left.png --right data/cones/right.png --height 256 --width 256 
python3 src/cpp/util_write.py --left data/virginia/left.png --right data/virginia/right.png --height 256 --width 256 
cd src/cpp
gcc -o stereoBM stereoBM.c
./stereoBM
cd -
python3 src/cpp/util_read.py
