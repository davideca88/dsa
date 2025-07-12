CC = gcc
CFLAGS = -Wall  -O3 -ffast-math
LDFLAGS = -lm
LIBDIR = lib
LIB = $(LIBDIR)/list.o $(LIBDIR)/vector.o $(LIBDIR)/avl_tree.o $(LIBDIR)/binary_tree.o $(LIBDIR)/benchmark.o \
	  $(LIBDIR)/hash_table.o $(LIBDIR)/index.o $(LIBDIR)/product.o $(LIBDIR)/graph.o
QUESTS = quest1 quest2 quest3 quest4

all: $(LIB)

$(LIBDIR):
	mkdir $@

$(LIB): $(LIBDIR)/%.o: src/%.c $(LIBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(QUESTS): %: %.c $(LIB)
	$(CC) $(CFLAGS) $(LIB) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(QUESTS) $(LIBDIR) *.txt *.bin
