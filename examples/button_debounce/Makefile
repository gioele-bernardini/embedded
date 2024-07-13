# I studied Makefiles during the OS course
# I just need to refresh the concepts and review the syntax,
# as it is not known for being particularly intuitive.
# I will keep the comments for completeness.


# Compiler name
CC = gcc

# Compiler options
CFLAGS = -Wall -Wextra -pedantic -std=c99

# Name of the executable file
TARGET = keyboard_event

# Source files
SRCS = keyboard_event.c

# Generated object files
OBJS = $(SRCS:.c=.o)

# Rule to compile the project
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean the project
clean:
	rm -f $(TARGET) $(OBJS)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

