CC      = gcc
CFLAGS  = -O3 -march=native -Wall -Wextra
TARGET  = glance
SRC     = glance.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm glance

.PHONY: all clean
