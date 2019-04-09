LIBS  = `xml2-config --cflags --libs` -lcrypto -lcurl
CFLAGS = -Wall

SRC=$(wildcard *.c)

main: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
debug: $(SRC)
	gcc -o $@ $^ $(CFLAGS) -g $(LIBS)
