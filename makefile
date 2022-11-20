FLAGS = -g -Wall -Wextra -std=c99

program.out: main.o suggest.o spell_checker.o IO.o trie.o tablahash.o queue.o strFunc.o int_str.o char_arr.o suggestion_struct.o
	$(CC) -o $@ $^ $(FLAGS)

main.o: main.c IO.o spell_checker.o
	$(CC) -c $< $(FLAGS)

IO.o: IO.c  strFunc.o trie.o
	$(CC) -c $< $(FLAGS)

suggest.o: suggest.c strFunc.o queue.o int_str.o trie.o
	$(CC) -c $< $(FLAGS)

spell_checker.o: spell_checker.c IO.o trie.o char_arr.o suggestion_struct.o
	$(CC) -c $< $(FLAGS)

tablahash.o: hashtable/tablahash.c
	$(CC) -c $< $(FLAGS)

trie.o: trie/trie.c
	$(CC) -c $< $(FLAGS)

queue.o: queue/queue.c
	$(CC) -c $< $(FLAGS)

suggestion_struct.o: type_operations/suggestion_struct.c strFunc.o
	$(CC) -c $< $(FLAGS)

strFunc.o: type_operations/strFunc.c
	$(CC) -c $< $(FLAGS)

int_str.o: type_operations/int_str.c
	$(CC) -c $< $(FLAGS)

char_arr.o: char_arr/char_arr.c
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm program.out

.PHONY = clean