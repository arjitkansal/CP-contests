g++-10 e.cpp
./a.out < input.txt > o1.txt
g++-10 b.cpp
./a.out < input.txt > o2.txt
diff o1.txt o2.txt
