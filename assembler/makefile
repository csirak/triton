# Variables
CC = gcc
CFLAGS =-Wall -Wextra -g -I$(LIBDIR)  # Include the header directory
LDFLAGS = 
SRCDIR = src
TESTDIR = tests
LIBDIR = lib
OBJDIR = obj
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
TESTS = $(wildcard $(TESTDIR)/*.c)
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(TESTS))
LIB_SOURCES = $(wildcard $(LIBDIR)/src/*.c)  # Adjusted for lib/src
LIB_OBJECTS = $(patsubst $(LIBDIR)/src/%.c,$(OBJDIR)/%.o,$(LIB_SOURCES))  # Adjusted for lib/src
TARGET = $(BINDIR)/assembler
TEST_TARGET = $(BINDIR)/assembler_test_suite

# Tell make where to find .c files
vpath %.c $(SRCDIR) $(TESTDIR) $(LIBDIR)/src  # Adjusted for lib/src

# Default target
all: $(TARGET) $(TEST_TARGET)

# Rule to create the object files
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the executable
$(TARGET): $(OBJECTS) $(LIB_OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJECTS) $(filter-out $(OBJDIR)/main.o, $(OBJECTS)) $(LIB_OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Target to compile and run tests
test: $(TEST_TARGET)
	@./$(TEST_TARGET) 

# Target to compile and run the main program
run: $(TARGET)
	echo "Running $(TARGET)...\n\nOutput:\n"
	@./$(TARGET) tests/test.tasm

# Clean up
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean test run