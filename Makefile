SRCDIR		= src
INCDIR  	= includes
BUILDDIR	= build
OBJDIR		= $(BUILDDIR)/obj
BINDIR		= $(BUILDDIR)/bin
TESTDIR		= test

CC			= gcc
TARGET	= backtracking
CFLAGS	= -Wall -Wextra -pedantic -g -O0 -I$(INCDIR) 
LFLAGS	=

SRC	:= $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS	:= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

REMOVE	:= rm -rf

# Linking
$(BINDIR)/$(TARGET): $(OBJECTS) # $(CMN_OBJ)
	mkdir -p $(BINDIR)
	$(CC) $(LFLAGS) -o $@ $(OBJECTS) # $(CMN_OBJ)
	@echo "Linking complete"

# Compilation
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@
# 	$(CC) -I$(INCLUDES) -MM -MT '$(OBJDIR)/$*.o' $(SRCDIR)/$*.c
	@echo "Compiled $<"


.PHONY: clean
clean:
	$(REMOVE) $(OBJECTS) $(OBJDIR) $(BINDIR)
	@echo "Deleted $<"

.PHONY: remove
remove:
	$(REMOVE) $(BINDIR)/$(TARGET)
	$(REMOVE) $(OBJECTS)
	@echo "Deleted $<"

.PHONY: run
run:
	$(BINDIR)/$(TARGET)

.PHONY: debug
debug:
	gdb $(BINDIR)/$(TARGET)

.PHONY: run_tests
run_tests:
	$(TESTDIR)/test_build/run_tests.sh

.PHONY: clean_tests
clean_tests:
	$(TESTDIR)/test_build/clean_tests.sh	

.PHONY: exe32 exe64
exe32: CC := i686-w64-mingw32-gcc
exe32: TARGET	:= backtracking32.exe 
	
exe32: clean all
	@echo 
	@echo "Built for windows 32 bit using gcc version: $(CC)\n Built to target $(BINDIR)/$(TARGET)"

exe64: CC := x86_64-w64-mingw32-gcc
exe64: TARGET	:= backtracking64.exe 
	
exe64: clean all
	@echo 
	@echo "Built for windows 64 bit using gcc version: $(CC)\n Built to target $(BINDIR)/$(TARGET)"

.PHONY: all
all: $(BINDIR)/$(TARGET)


# 	sudo apt-get install mingw-w64
# Then you can create 32-bit Windows executable with:

# i686-w64-mingw32-gcc -o main32.exe main.c
# And 64-bit Windows executable with:

# x86_64-w64-mingw32-gcc -o main64.exe main.c