# These are variables. We usually define CC, CCLINK, CFLAGS, and OBJS
CC=gcc
CCLINK=$(CC) # Read variable CC using $(CC)
CFLAGS=-g -Wall -std=c99
OBJS=ransom.o
EXEC=prog.exe
RM=rm -fr *.exe $(OBJS)
# The first rule is invoked by default.
# We can also invoke it (or any other rule) manually with "make all" - 
# note that "all" is the rule's name!
$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

ransom.o: ransom.c
	$(CC) $(CFLAGS) -c ransom.c



# Custom rule - we can invoke it manually by calling "make clean"
# We usually have a "clean" rule to delete any automatically generated files
clean:
	$(RM)