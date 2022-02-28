CC=gcc
WFLAGS=-Wall -g

all:
	$(CC) logger.c utility.c url_parser.c packet_resolver.c dns_client.c main.c -o main
clean:
	rm -f main
