CFLAGS = -fpic -coverage -lm -std=c99 -ftest-coverage -fprofile-arcs

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

testingtools.o: testingtools.c testingtools.h
	gcc -c testingtools.c -g $(CFLAGS)
	
unittest1.o: unittest1.c
	gcc -c unittest1.c -g $(CFLAGS)

unittest2.o: unittest2.c
	gcc -c unittest2.c -g $(CFLAGS)

unittest3.o: unittest3.c
	gcc -c unittest3.c -g $(CFLAGS)
	
unittest4.o: unittest4.c
	gcc -c unittest4.c -g $(CFLAGS)

cardtest1.o: cardtest1.c
	gcc -c cardtest1.c -g $(CFLAGS)

cardtest2.o: cardtest2.c
	gcc -c cardtest2.c -g $(CFLAGS)

cardtest3.o: cardtest3.c
	gcc -c cardtest3.c -g $(CFLAGS)

cardtest4.o: cardtest4.c
	gcc -c cardtest4.c -g $(CFLAGS)

unittestresults.out: dominion.o rngs.o unittest1.o unittest2.o unittest3.o unittest4.o cardtest1.o cardtest2.o cardtest3.o cardtest4.o testingtools.o 
	gcc -o test.run -g dominion.o rngs.o unittest1.o testingtools.o $(CFLAGS)
	./test.run 1234 > unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./test.run 1234
	gcc -o test.run -g dominion.o rngs.o unittest2.o testingtools.o $(CFLAGS)
	./test.run 1234 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./test.run 1234
	gcc -o test.run -g dominion.o rngs.o unittest3.o testingtools.o $(CFLAGS)
	./test.run 1234 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./test.run 1234
	gcc -o test.run -g dominion.o rngs.o unittest4.o testingtools.o $(CFLAGS)
	./test.run 1234 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./test.run 1234
	gcc -o test.run -g dominion.o rngs.o cardtest1.o testingtools.o $(CFLAGS)
	./test.run 1234 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./test.run 1234
	gcc -o test.run -g dominion.o rngs.o cardtest2.o testingtools.o $(CFLAGS)
	./test.run 1234 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./test.run 1234
	gcc -o test.run -g dominion.o rngs.o cardtest3.o testingtools.o $(CFLAGS)
	./test.run 1234 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./test.run 1234
	gcc -o test.run -g dominion.o rngs.o cardtest4.o testingtools.o $(CFLAGS)
	./test.run 1234 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./test.run 1234

randomtestcard1.o: randomtestcard1.c
	gcc -c randomtestcard1.c -g $(CFLAGS)

randomtestadventurer.o: randomtestadventurer.c
	gcc -c randomtestadventurer.c -g $(CFLAGS)

randomtestcard2.o: randomtestcard2.c
	gcc -c randomtestcard2.c -g $(CFLAGS)

randomtestresults.out: dominion.o rngs.o testingtools.o randomtestcard1.o randomtestcard2.o randomtestadventurer.o
	gcc -o test.run -g dominion.o rngs.o testingtools.o randomtestcard1.o $(CFLAGS)
	./test.run 1234 >> randomtestresults.out
	gcov dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	./test.run 1234
	gcc -o test.run -g dominion.o rngs.o testingtools.o randomtestcard2.o $(CFLAGS)
	./test.run 1234 >> randomtestresults.out
	gcov dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	./test.run 1234
	gcc -o test.run -g dominion.o rngs.o testingtools.o randomtestadventurer.o $(CFLAGS)
	./test.run 1234 >> randomtestresults.out
	gcov dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	./test.run 1234
	

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so test.run
