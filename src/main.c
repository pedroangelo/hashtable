#include "hashtable.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *alphabet = "abcdefghijklmnopqrstuvwxyz";
	hashtable_t *hashtable = create_ht(10, 0.1, 10, true);
  statistics_ht(hashtable);
  insert_ht(hashtable, "a", "a");
  insert_ht(hashtable, "a", "a");
	insert_ht(hashtable, "b", "b");
	insert_ht(hashtable, "c", "c");
	insert_ht(hashtable, "d", "d");
	insert_ht(hashtable, "e", "e");
  insert_ht(hashtable, "f", "f");
	insert_ht(hashtable, "g", "g");
  insert_ht(hashtable, "h", "alternative");
  printf("%s", retrieve_ht(hashtable, "g"));
  statistics_ht(hashtable);
  snapshot_ht(hashtable);
  delete_ht(hashtable);

  /* insert_ht(hashtable, "a", "a"); */
  /* insert_ht(hashtable, "a", "a"); */
	/* insert_ht(hashtable, "b", "b"); */
	/* insert_ht(hashtable, "c", "c"); */
	/* insert_ht(hashtable, "d", "d"); */
	/* insert_ht(hashtable, "e", "e"); */
  /* snapshot_ht(hashtable); */
  /* insert_ht(hashtable, "f", "f"); */
  /* snapshot_ht(hashtable); */
	/* insert_ht(hashtable, "g", "g"); */
	/* insert_ht(hashtable, "h", "h"); */
	/* insert_ht(hashtable, "i", "i"); */
	/* insert_ht(hashtable, "j", "j"); */
	/* insert_ht(hashtable, "k", "k"); */
	/* insert_ht(hashtable, "l", "l"); */
	/* insert_ht(hashtable, "m", "m"); */
	/* insert_ht(hashtable, "n", "n"); */
	/* insert_ht(hashtable, "o", "o"); */
	/* insert_ht(hashtable, "p", "p"); */
	/* insert_ht(hashtable, "q", "q"); */
	/* insert_ht(hashtable, "r", "r"); */
	/* insert_ht(hashtable, "s", "s"); */
	/* insert_ht(hashtable, "t", "t"); */
	/* insert_ht(hashtable, "u", "u"); */
	/* insert_ht(hashtable, "v", "v"); */
	/* insert_ht(hashtable, "w", "w"); */
	/* insert_ht(hashtable, "x", "x"); */
	/* insert_ht(hashtable, "y", "y"); */
	/* insert_ht(hashtable, "z", "z"); */
  /* remove_ht(hashtable, "a"); */
  /* remove_ht(hashtable, "b"); */
  /* remove_ht(hashtable, "c"); */
  /* remove_ht(hashtable, "d"); */
  /* remove_ht(hashtable, "e"); */
  /* remove_ht(hashtable, "f"); */
  /* remove_ht(hashtable, "g"); */
  /* remove_ht(hashtable, "h"); */
  /* remove_ht(hashtable, "i"); */
  /* remove_ht(hashtable, "j"); */
  /* remove_ht(hashtable, "k"); */
  /* remove_ht(hashtable, "l"); */
  /* remove_ht(hashtable, "m"); */
  /* remove_ht(hashtable, "n"); */
  /* remove_ht(hashtable, "o"); */
  /* remove_ht(hashtable, "p"); */
  /* remove_ht(hashtable, "q"); */
  /* remove_ht(hashtable, "r"); */
  /* remove_ht(hashtable, "s"); */
  /* remove_ht(hashtable, "t"); */
  /* remove_ht(hashtable, "u"); */
	/* remove_ht(hashtable, "v"); */
	/* remove_ht(hashtable, "w"); */
	/* remove_ht(hashtable, "x"); */
	/* remove_ht(hashtable, "y"); */
  /* statistics_ht(hashtable); */
	/* remove_ht(hashtable, "z"); */
  /* snapshot_ht(hashtable); */
  /* insert_ht(hashtable, "a", "a"); */
  /* statistics_ht(hashtable); */
	/* snapshot_ht(hashtable); */
	return 1;
}
