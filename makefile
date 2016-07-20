## DIRECTORIES ##
SRCDIR = src
BINDIR = bin
OBJDIR = obj

## FILES ##
TARGET = hashtable
EXECFILE = main

# produce executable file
all: $(BINDIR)/$(EXECFILE)

# compile object file hashtable.o and store in obj directory
$(OBJDIR)/$(TARGET).o: $(SRCDIR)/$(TARGET).c $(SRCDIR)/$(TARGET).h
	gcc -c $(SRCDIR)/$(TARGET).c -o $(OBJDIR)/$(TARGET).o

# compile object file main.o and store in obj directory
$(OBJDIR)/$(EXECFILE).o: $(SRCDIR)/$(EXECFILE).c
	gcc -c $(SRCDIR)/$(EXECFILE).c -o $(OBJDIR)/$(EXECFILE).o

# link object files main.o and hashtable.o and produce final executable
$(BINDIR)/$(EXECFILE): $(OBJDIR)/$(TARGET).o $(OBJDIR)/$(EXECFILE).o
	gcc $(OBJDIR)/$(EXECFILE).o $(OBJDIR)/$(TARGET).o -o $(BINDIR)/$(EXECFILE)

.PHONY: clean

clean:
	rm $(BINDIR)/*
	rm $(OBJDIR)/*

## List symbols with nm
