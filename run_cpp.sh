python3 src/cpp/util_write.py --left data/cones/right.png --right data/cones/left.png 
cd src/cpp
gcc -o stereoBM stereoBM.c
./stereoBM
cd -
python3 src/cpp/util_read.py
