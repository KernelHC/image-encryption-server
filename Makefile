CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -pthread

SRCS = queue.h queue.c queue_test.c
OBJS = queue.o queue_test.o
BIN = queue_test

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

queue_test.o: queue_test.c queue.c queue.h
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c $< -o $@

server.o: server.c
	$(CC) $(CFLAGS) -c $< -o $@

tree.o: tree.h tree.c
	$(CC) $(CFLAGS) -c $< -o $@

hashf.o: hashf.c hashf.h
	$(CC) $(CFLAGS) -c $< -o $@

caes.o: caes.h caes.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(OBJS)
	$(RM) $(BIN)