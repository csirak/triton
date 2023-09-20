# Variables
CC = gcc
SRCDIR = src
TESTDIR = tests
LIBDIR = ../lib
LIBSDIR = ../lib/src
OBJDIR = obj
BINDIR = bin

# Update include directories in CFLAGS
CFLAGS = -I.. -I$(LIBSDIR) -Wall -Wextra -g

# Define sources and objects
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

TESTS = $(wildcard $(TESTDIR)/*.c)
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(TESTS))

LIB_SOURCES = $(wildcard $(LIBDIR)/*.c)
LIB_OBJECTS = $(patsubst $(LIBDIR)/%.c,$(OBJDIR)/%.o,$(LIB_SOURCES))

LIBS_SOURCES = $(wildcard $(LIBSDIR)/*.c)
LIBS_OBJECTS = $(patsubst $(LIBSDIR)/%.c,$(OBJDIR)/%.o,$(LIBS_SOURCES))

TARGET = $(BINDIR)/core
TEST_TARGET = $(BINDIR)/core_test_suite

# Update vpath to find .c files from all directories
vpath %.c $(SRCDIR) $(TESTDIR) $(LIBDIR) $(LIBSDIR)

# Default target
all: $(TARGET) $(TEST_TARGET)

# Rule to create the object files
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the executable
$(TARGET): $(OBJECTS) $(LIB_OBJECTS) $(LIBS_OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJECTS) $(filter-out $(OBJDIR)/main.o, $(OBJECTS)) $(LIB_OBJECTS) $(LIBS_OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Target to compile and run tests
test: $(TEST_TARGET)
	@./$(TEST_TARGET)

# Target to compile and run the main program
run: $(TARGET)
	echo "Running $(TARGET)...\n\nOutput:\n"
	@./$(TARGET) tests/test.tasm test.bin

# Clean up
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean test run
