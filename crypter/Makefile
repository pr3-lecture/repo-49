.PHONY: all clean
all: encrypt decrypt runtest

clean:
	rm -f encrypt decrypt test run.o crypto.o testForCrypter.o

run.o: run.c
	cc -Wall -c run.c

crypto.o: crypto.c
	cc -Wall -c crypto.c

testForCrypter.o: testForCrypter.c
	cc -Wall -c testForCrypter.c

encrypt: run.o crypto.o
	cc -o encrypt run.o crypto.o

decrypt: run.o crypto.o
	cc -o decrypt run.o crypto.o

runtest: testForCrypter.o crypto.o
	cc -o test testForCrypter.o crypto.o
	./test
