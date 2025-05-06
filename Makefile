CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
OBJ = obj/list.o obj/vector.o obj/avl_tree.o obj/binary_tree.o obj/benchmark.o 
QUESTS = quest1 quest2 quest3 quest4

all: $(QUESTS)
	
obj/%.o: src/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(QUESTS): %: %.c $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(QUESTS) $(OBJ)
