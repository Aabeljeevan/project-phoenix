# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -Iinclude

# Source Files
SRC = main.c \
      src/can.c

# Output Executable
TARGET = uds_server

# Default Target
all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean Build Files
clean:
	rm -f $(TARGET) *.o