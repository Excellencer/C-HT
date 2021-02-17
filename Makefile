HT: HT.o ali1.o ali2.o
	gcc HT.o ali1.o ali2.o -o HT -std=c99 -Wall
HT.o: HT.c ali1.h ali2.h
	gcc HT.c -c -std=c99 -Wall
ali1.o: ali1.c ali1.h ali2.h
	gcc ali1.c -c -std=c99 -Wall
ali2.o: ali2.c ali2.h ali1.h
	gcc ali2.c -c -std=c99 -Wall
