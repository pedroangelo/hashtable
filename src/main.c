#include "hashtable.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	hashtable_t *hashtable = create_ht(1, 0.1, 0.75);

	char *alphabet = "abcdefghijklmnopqrstuvwxyz";
	insert_ht(hashtable, "a", "a");
	insert_ht(hashtable, "b", "b");
	insert_ht(hashtable, "c", "c");
	insert_ht(hashtable, "d", "d");
	insert_ht(hashtable, "e", "e");
	insert_ht(hashtable, "f", "f");
	insert_ht(hashtable, "g", "g");
	insert_ht(hashtable, "h", "h");
	insert_ht(hashtable, "i", "i");
	insert_ht(hashtable, "j", "j");
	insert_ht(hashtable, "k", "k");
	insert_ht(hashtable, "l", "l");
	insert_ht(hashtable, "m", "m");
	insert_ht(hashtable, "n", "n");
	insert_ht(hashtable, "o", "o");
	insert_ht(hashtable, "p", "p");
	insert_ht(hashtable, "q", "q");
	insert_ht(hashtable, "r", "r");
	insert_ht(hashtable, "s", "s");
	insert_ht(hashtable, "t", "t");
	insert_ht(hashtable, "u", "u");
	insert_ht(hashtable, "v", "v");
	insert_ht(hashtable, "w", "w");
	insert_ht(hashtable, "x", "x");
	insert_ht(hashtable, "y", "y");
	insert_ht(hashtable, "z", "z");
	statistics_ht(hashtable);
	snapshot_ht(hashtable);
	delete_ht(hashtable);
	return 1;
}
