# I studied Makefiles during the OS course
# I just need to refresh the concepts and review the syntax,
# as it is not known for being particularly intuitive.
# I will keep the comments for completeness.

# Compiler name
CXX = g++

# Compiler options
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

# Name of the executable file
TARGET = keyboard_event

# Source files
SRCS = main.cpp TerminalConfig.cpp

# Generated object files
OBJS = $(SRCS:.cpp=.o)

# Rule to compile the project
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the project
clean:
	rm -f $(TARGET) $(OBJS)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

