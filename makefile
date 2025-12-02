all:	jaccard

jaccard:	jaccard.o
			g++ -std=c++11 -Wextra -Wall -Wno-unused-parameter jaccard.o -o jaccard

jaccard.o:	jaccard.cpp
			g++ -c -g -std=c++11 -Wextra -Wall -Wno-unused-parameter jaccard.cpp -o jaccard.o

clean:		
		rm jaccard.o jaccard