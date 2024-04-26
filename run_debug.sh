python3 src/cpp/util_debug.py --left data/cones/left.png --right data/cones/right.png 
# python3 src/cpp/util_write.py --left data/lab/left.png --right data/lab/right.png
cd src/cpp
gcc -o stereoBM stereoBM.c
./stereoBM
cd -
python3 src/cpp/util_debug_disp.py
