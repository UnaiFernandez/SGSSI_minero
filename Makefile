# Minero makefile
# Unai Fernandez
# 2021-10-18

CC = gcc
CFLAGS = -lcrypto -lssl
OBJ=BTC_miner

#gcc sha.c -o sha -lcrypto -lssl

all:
	$(CC) src/BTC_miner.c src/sha256calc.c -o $(OBJ) $(CFLAGS)
exec:
	./BTC_miner $(file) $(zeros)
clean:
	rm -rf BTC_miner
	rm -rf *.o
	rm new*
