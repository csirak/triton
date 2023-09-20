# Variables
CC = gcc
CFLAGS = -Ilib -I/opt/homebrew/include -I/opt/homebrew/include/CSFML -Wall -Wextra -g
LDFLAGS = -L/opt/homebrew/lib -lcsfml-graphics -lcsfml-window -lcsfml-system
SRCDIR = src
TESTDIR = tests
LIBDIR = lib
OBJDIR = obj
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
TESTS = $(wildcard $(TESTDIR)/*.c)
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(TESTS))
LIB_SOURCES = $(wildcard $(LIBDIR)/*.c)
LIB_OBJECTS = $(patsubst $(LIBDIR)/%.c,$(OBJDIR)/%.o,$(LIB_SOURCES))
TARGET = $(BINDIR)/core
TEST_TARGET = $(BINDIR)/core_test_suite

# Tell make where to find .c files
vpath %.c $(SRCDIR) $(TESTDIR) $(LIBDIR)

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
	@./$(TARGET)

# Clean up
clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean test run
