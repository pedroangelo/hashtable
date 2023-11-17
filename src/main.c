#include "hashtable.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *alphabet = "abcdefghijklmnopqrstuvwxyz";
  hashtable_t *hashtable = ht_create(10, -1, 10, true);
  ht_insert(hashtable, "a", "a");
  ht_insert(hashtable, "a", "a");
  ht_insert(hashtable, "b", "b");
  ht_insert(hashtable, "c", "c");
  ht_insert(hashtable, "d", "d");
  ht_insert(hashtable, "e", "e");
  ht_insert(hashtable, "f", "f");
  ht_insert(hashtable, "g", "g");
  ht_insert(hashtable, "h", "alternative");
  printf("%s", ht_retrieve(hashtable, "g"));
  ht_statistics(hashtable);
  ht_snapshot(hashtable);
  ht_remove(hashtable, "a");
  ht_snapshot(hashtable);
  ht_statistics(hashtable);
  ht_delete(hashtable);
  return 1;
}
