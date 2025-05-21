CC = gcc
CFLAGS = -Wall -Werror -O3 -ffast-math
LDFLAGS = -lm
LIBDIR = lib
LIB = $(LIBDIR)/list.o $(LIBDIR)/vector.o $(LIBDIR)/avl_tree.o $(LIBDIR)/binary_tree.o $(LIBDIR)/benchmark.o 
QUESTS = quest1 quest2 quest3 quest4

all: $(QUESTS)

$(LIBDIR):
	mkdir $@

$(LIB): $(LIBDIR)/%.o: src/%.c $(LIBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(QUESTS): %: %.c $(LIB)
	$(CC) $(CFLAGS) $(LIB) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(QUESTS) $(LIBDIR) *.txt *.bin
