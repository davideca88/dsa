CC = gcc
CFLAGS = -Wall -Werror -O3 -ffast-math
LDFLAGS = -lm
OBJDIR = obj
OBJ = $(OBJDIR)/list.o $(OBJDIR)/vector.o $(OBJDIR)/avl_tree.o $(OBJDIR)/binary_tree.o $(OBJDIR)/benchmark.o 
QUESTS = quest1 quest2 quest3 quest4

all: $(QUESTS)

$(OBJDIR):
	mkdir $@

$(OBJ): $(OBJDIR)/%.o: src/%.c $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(QUESTS): %: %.c $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(QUESTS) $(OBJDIR) *.txt *.bin
