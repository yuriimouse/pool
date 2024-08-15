VERSION = 2.2.1

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -std=gnu99 -DVERSION=\"$(VERSION)\" -I/usr/local/include -I/usr/include 
LDFLAGS = -fpie -L$(LIB_PATH)lib/

S_LIBS = -Wl,-Bstatic -L/usr/lib64 -lcunit -lpool
D_LIBS = -Wl,-Bdynamic -L/usr/lib64 -lpthread -lresolv -lcjson
TARGET_BIN = unitTest

.PHONY: default
default: $(TARGET_BIN) clean

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_BIN): $(OBJECTS)
	$(CC) ${LDFLAGS} -o $@ $(OBJECTS) $(S_LIBS) $(D_LIBS)

.PHONY: clean
clean:
	rm -f *.o
