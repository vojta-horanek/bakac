LIBS  = `xml2-config --cflags --libs` -lcrypto -lcurl -g
CFLAGS = -Wall

SRC=$(wildcard *.c)

main: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
