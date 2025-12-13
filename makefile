all:	jaccard lcs

jaccard:	jaccard.o
			g++ -std=c++17 -O2 -Wextra -Wall -Wno-unused-parameter jaccard.o -o jaccard

jaccard.o:	jaccard.cpp
			g++ -c -g -std=c++17 -O2 -Wextra -Wall -Wno-unused-parameter jaccard.cpp -o jaccard.o

lcs: lcs.o
			g++ -std=c++11 -Wextra -Wall -Wno-unused-parameter lcs.o -o lcs

lcs.o:	lcs.cpp
			g++ -c -g -std=c++11 -Wextra -Wall -Wno-unused-parameter lcs.cpp -o lcs.o

clean:		
		rm jaccard.o jaccard lcs.o lcs
