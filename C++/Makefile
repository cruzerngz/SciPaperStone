CC = g++
EXT = cpp
CPPFLAGS = -Wall
CFLAGS =

SRCDIR = src
BINDIR = bin
OBJDIR = obj
TESTDIR = test

TARGET = SciPaperStone

mkdir-no-exist=@mkdir -p $(@D)

all: $(BINDIR)/$(TARGET)
allobj: $(foreach object, $(TARGET), $(OBJDIR)/$(object).o)

debug:: CFLAGS += -g
debug:: cleanobj
debug:: all

clean: cleanobj cleanbin

cleanobj:
	@rm -vf $(OBJDIR)/*

cleanbin:
	@rm -vf $(BINDIR)/*

$(OBJDIR)/%.o: $(SRCDIR)/%.$(EXT)
	$(mkdir-no-exist)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

## bin directory compilation - executable
$(BINDIR)/%: $(OBJDIR)/%.o
	$(mkdir-no-exist)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@
