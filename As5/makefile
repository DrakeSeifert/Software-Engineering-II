CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c
	echo "Results for unit tests:" > unittestresults.out
	
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 unittest1.c dominion.c rngs.c $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 unittest2.c dominion.c rngs.c $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 unittest3.c dominion.c rngs.c $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 unittest4.c dominion.c rngs.c $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 cardtest2.c dominion.c rngs.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 cardtest3.c dominion.c rngs.c $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	# echo "cardtest4.c:" >> unittestresults.out
	# gcc -o cardtest4 cardtest4.c dominion.c rngs.c $(CFLAGS)
	# cardtest4 >> unittestresults.out
	# gcov -b -f dominion.c >> unittestresults.out

randomTestResults.out: randomTestCard1.c randomTestCard2.c randomTestAdventurer.c

	echo "randomTestAdventurer.c" > randomTestAdventurer.out
	gcc -o randomTestAdventurer randomTestAdventurer.c dominion.c rngs.c $(CFLAGS)
	randomTestAdventurer >> randomTestAdventurer.out
	gcov -b -f dominion.c >> randomTestAdventurer.out

	echo "randomTestCard1.c" > randomTestCard1.out
	gcc -o randomTestCard1 randomTestCard1.c dominion.c rngs.c $(CFLAGS)
	randomTestCard1 >> randomTestCard1.out
	gcov -b -f dominion.c >> randomTestCard1.out

	echo "randomTestCard2.c" > randomTestCard2.out
	gcc -o randomTestCard2 randomTestCard2.c dominion.c rngs.c $(CFLAGS)
	randomTestCard2 >> randomTestCard2.out
	gcov -b -f dominion.c >> randomTestCard2.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o randomTestCard1 randomTestCard2 randomTestAdventurer cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 unittestresults.out playdom.exe playdom test.exe test player player.exe testInit testInit.exe testDrawCard badTestDrawCard *.gcov *.gcda *.gcno *.so a.out
