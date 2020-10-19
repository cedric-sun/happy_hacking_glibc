all: client server

client: client.o
	$(CC) -lpthread -o client client.o

server: server.o
	$(CC) -lpthread -o server server.o

client.o:client.c
	$(CC) -c client.c

server.o:server.c
	$(CC) -c server.c

clean:
	rm -f *.o client server
