#include "hashtable.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	hashtable_t *hashtable = create_ht(10);
	insert_ht(hashtable, "key1", "a");
	insert_ht(hashtable, "key2", "b");
	insert_ht(hashtable, "key3", "c");
	insert_ht(hashtable, "key4", "d");
	insert_ht(hashtable, "key5", "e");
	insert_ht(hashtable, "key6", "f");
	statistics_ht(hashtable);
	delete_ht(hashtable);
	return 1;
}
