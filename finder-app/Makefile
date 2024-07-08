# Define the source directory
SRCDIR = ./

# Define the target executable
TARGET = ${SRCDIR}/writer

# Define the source files
SRCS = ${SRCDIR}/writer.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the compiler and flags
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -Werror -std=gnu99

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
