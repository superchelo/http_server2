# Compiler and flags
CC = gcc
CFLAGS = -w
LDFLAGS = -lpthread

# Project name
TARGET = myserver

# Source and object files
SRCS = main.c connection.c
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Linking step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compilation step for .c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

