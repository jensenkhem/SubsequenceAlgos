a3: main.o utility.o lcs.o lts.o lps.o
	gcc -Wall -std=c99 main.o lcs.o lts.o lps.o utility.o -o a3

main.o: main.c main.h
	gcc -Wall -std=c99 -c main.c

utility.o: utility.c utility.h 
	gcc -Wall -std=c99 -c utility.c

lcs.o: lcs.c lcs.h
	gcc -Wall -std=c99 -c lcs.c

lts.o: lts.c lts.h 
	gcc -Wall -std=c99 -c lts.c

lps.o: lps.c lps.h 
	gcc -Wall -std=c99 -c lps.c

clean:
	rm -f *.out *.o