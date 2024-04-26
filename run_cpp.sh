# python3 src/cpp/util_write.py --left data/tunnel/left.png --right data/tunnel/right.png 
python3 src/cpp/util_write.py --left data/sewer/left.png --right data/sewer/right.png
cd src/cpp
gcc -o stereoBM stereoBM.c
./stereoBM
cd -
python3 src/cpp/util_read.py
