python3 src/cpp/util_write.py --left data/lotus/lotus-left.png --right data/lotus/lotus-right.png 
cd src/cpp
gcc -o stereoBM stereoBM.c
./stereoBM
cd -
python3 src/cpp/util_read.py
