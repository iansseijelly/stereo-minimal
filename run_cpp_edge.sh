# python3 src/cpp/util_write.py --left data/virginia/left.png --right data/virginia/right.png --height 512 --width 512 
python3 src/cpp/util_write.py --left data/motorcycle/left.png --right data/motorcycle/right.png --height 512 --width 512 
cd src/cpp
gcc -o edgeSobel edgeSobel.c -lm
./edgeSobel
cd -
python3 src/cpp/util_read.py
