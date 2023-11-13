/*
 * Simple Hashmap Implementation in C
 *
 * Author: Pedro Ângelo
 * Date: September 2016
 */

// INCLUDES
#include "hashtable.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// MACROS

// GLOBAL VARIABLES

// MAIN FUNCTIONS DEFINITIONS

// create a empty hashtable and return the address
hashtable_t *create_ht(int size, float min_load_factor, float max_load_factor, bool enable_feedback) {
  
	int i;
	// allocate space for the hashtable
	hashtable_t *hashtable = malloc(sizeof(hashtable_t));
	// set hashtable size
	hashtable->size = size;
	// set current number of buckets
	hashtable->num_buckets = 0;
	// set hashtable min load factor
	hashtable->min_load_factor = min_load_factor;
  // set hashtable max load factor
	hashtable->max_load_factor = max_load_factor;
  // set hashtable enable_feedback variable
  hashtable->enable_feedback = enable_feedback;
	// create entries, i.e. array of pointers to buckets
	hashtable->entries = malloc(size * sizeof(bucket_t));

  // initialize entries
	for(i=0;i<size;i++) hashtable->entries[i] = (bucket_t *) NULL;

  // print status messages
  if (enable_feedback) printf("Hashtable creation successful: with size %d and %.0f%% min / %.0f%% max load limits\n", size, (100 * hashtable->min_load_factor), (100 * hashtable->max_load_factor));
  
	return hashtable;
}

// deallocates the space used by the hash table
void delete_ht(hashtable_t *hashtable) {

  // free entries
  int freed_buckets = deallocate_all_entries(hashtable->entries, hashtable->size);

  // print status messages
  if (hashtable->enable_feedback) printf("Hashtable deletion successful: %d buckets freed\n", freed_buckets);

  // free hashtable
  free(hashtable);
}

/* // insert (key, value) pair in hash */
/* void insert_ht(hashtable_t *hashtable, char *key, char *value) { */

/*   // check if key already exists, if so do nothing */
/*   if(check_key(hashtable, key) == true) { */
/*     // print status messages */
/*     if (hashtable->enable_feedback) printf("Hashtable insertion failed: key %s already in use\n", key); */
    
/*     return; */
/*   } */

/*   // get new bucket */
/*   bucket_t *new_bucket = create_bucket(key, value); */
/*   // get hash value of key */
/*   uint32_t hash = jenkins_one_at_a_time_hash(key, strlen(key)); */
/*   // get index from hash */
/*   int index = hash % hashtable->size; */
/*   // get entry in index position */
/*   entry_t *entry = &hashtable->entries[index]; */
/*   // if there is no bucket in entry */
/*   if(entry->size == 0) { */
/*     entry->first_bucket = new_bucket; */
/*     entry->last_bucket = new_bucket; */

/*     // if there is a collision */
/*   } else { */
/*     // get last bucket */
/*     bucket_t *last = entry->last_bucket; */
/*     // point last bucket's next to new_bucket */
/*     last->next = (struct bucket_t *) new_bucket; */
/*     // point entry's last bucket to new bucket */
/*     entry->last_bucket = new_bucket; */
/*   } */
/*   // increment counters */
/*   entry->size++; */
/*   hashtable->num_buckets++; */

/*   // print status messages */
/*   if (hashtable->enable_feedback) printf("Hashtable insertion successful: pair (%s, %s) inserted\n", key, value); */
  
/*   // check if hashtable needs resizing */
/*   if(hashtable->num_buckets >= hashtable->size * hashtable->max_load_factor) resize_ht(hashtable, hashtable->size*2); */
/* } */

/* // retrieve value given the key */
/* char *retrieve_ht(hashtable_t *hashtable, char *key) { */

/*   // get hash value of key */
/*   uint32_t hash = jenkins_one_at_a_time_hash(key, strlen(key)); */
/*   // get index from hash */
/*   int i, index = hash % hashtable->size; */
/*   // get entry in index position */
/*   entry_t *entry = &hashtable->entries[index]; */
/*   // get first bucket */
/*   bucket_t *current_bucket = entry->first_bucket; */
/*   // search for key */
/*   for(i=0;i<entry->size;i++) { */
/*     // if keys match, return value */
/*     if(strcmp(current_bucket->key, key) == 0) { */

/*       // print status messages */
/*       if (hashtable->enable_feedback) printf("Hashtable retrieval successful: value %s for key %s retrived\n", current_bucket->value, key); */
      
/*       return current_bucket->value; */
/*     } */
/*     // place next bucket in current_bucket */
/*     current_bucket = (bucket_t *) current_bucket->next; */
/*   } */
  
/*   // print status messages */
/*   if (hashtable->enable_feedback) printf("Hashtable retrieval failed: no value for key %s\n", key); */
  
/*   return NULL; */
/* } */

/* // remove value given the key and return it */
/* char *remove_ht(hashtable_t *hashtable, char *key) { */

/*   // get hash value of key */
/*   uint32_t hash = jenkins_one_at_a_time_hash(key, strlen(key)); */
/*   // get index from hash */
/*   int i, index = hash % hashtable->size; */
/*   // get entry in index position */
/*   entry_t *entry = &hashtable->entries[index]; */
/*   // get first bucket */
/*   bucket_t *current_bucket = entry->first_bucket; */
/*   // variable that holds previous bucket */
/*   bucket_t *previous_bucket = entry->first_bucket; */
/*   // search for key */
/*   for(i=0;i<entry->size;i++) { */
/*     // if keys match */
/*     if(strcmp(current_bucket->key, key) == 0) { */
/*       // store value */
/*       char* value = current_bucket->value; */

/*       // update entry pointers and next bucket pointer */

/*       // entry only has one bucket */
/*       if(entry->size == 1) { */
/*         entry->first_bucket = NULL; */
/*         entry->last_bucket = NULL; */
/*       } */

/*       // entry has more than one bucket */
/*       else { */
/*         // removing first bucket, set first bucket to next bucket */
/*         if(i == 0) entry->first_bucket = (bucket_t *) current_bucket->next; */
/*         // removing last bucket */
/*         if(i == entry->size-1) { */
/*           entry->last_bucket = (bucket_t *) previous_bucket; */
/*           previous_bucket->next = NULL; */
/*         } */
/*         // removing bucket that isn't first or last bucket, , update pointer to next bucket */
/*         if(i != 0 && i != entry->size-1) previous_bucket->next = current_bucket->next; */
/*       } */

/*       // free current bucket */
/*       free(current_bucket); */
/*       // decrement counters */
/*       entry->size--; */
/*       hashtable->num_buckets--; */

/*       // print status messages */
/*       if (hashtable->enable_feedback) printf("Hashtable removal successful: value %s for key %s removed\n", value, key); */

/*       // check if hashtable needs resizing */
/*       if(hashtable->num_buckets <= hashtable->size * hashtable->min_load_factor) { */
/*         // resize hashtable */
/*         resize_ht(hashtable, hashtable->size / 2); */
/*       } */
      
/*       // return value; */
/*       return value; */
/*     } */
/*     // place next bucket in current_bucket */
/*     current_bucket = (bucket_t *) current_bucket->next; */
/*     if(i!=0) previous_bucket = (bucket_t *) previous_bucket->next; */
/*   } */

/*   // print status messages */
/*   if (hashtable->enable_feedback) printf("Hashtable removal failed: no value for key %s\n", key); */
  
/*   return NULL; */
/* } */

/* // resize hashtable */
/* void resize_ht(hashtable_t *hashtable, int size) { */

/*   int i, j; */

/*   // get old size */
/*   int old_size = hashtable->size; */

/*   // create new entry table */
/*   entry_t *new_entries = malloc(size * sizeof(entry_t)); */

/*   // old entry table */
/*   entry_t *old_entries = hashtable->entries; */

/*   // initialize entries */
/*   for(i=0;i<size;i++) { */
/*     new_entries[i].size = 0; */
/*     new_entries[i].first_bucket = (bucket_t *) NULL; */
/*     new_entries[i].last_bucket = (bucket_t *) NULL; */
/*   } */

/*   // change hashtable variables */
/*   hashtable->size = size; */
/*   hashtable->entries = new_entries; */
/*   hashtable->num_buckets = 0; */

/*   // temporary variables */
/*   entry_t current_entry; */
/*   bucket_t *current_bucket; */

/*   bool enable_feedback = hashtable->enable_feedback; */
/*   // temporarily disable feedback */
/*   hashtable->enable_feedback = false; */

/*   // re-hash all buckets to new */
/*   // for each entry */
/*   for(i=0;i<old_size;i++) { */

/*     // get entry from entry list */
/*     current_entry = old_entries[i]; */
/*     // get first bucket */
/*     current_bucket = current_entry.first_bucket; */
/*     // for each bucket in entry */
/*     for(j=0;j<current_entry.size;j++) { */
/*       // insert (key, value) pair in new hashtable */
/*       insert_ht(hashtable, (char *) current_bucket->key, (char *) current_bucket->value); */
/*       // iterate to next bucket */
/*       current_bucket = (bucket_t *) current_bucket->next; */
/*     } */
/*   } */

/*   // deallocate old entry list */
/*   deallocate_entries(old_entries, old_size); */
  
/*   // restore feedback */
/*   hashtable->enable_feedback = enable_feedback; */
/*   // print status messages */
/*   if (hashtable->enable_feedback) { */
/*     printf("Hashtable successfully resized: from size %d to size %d\n", old_size, size); */
/*   } */
/* } */

// INFORMATIVE FUNCTIONS DEFINITIONS

// collect statistics from hashtable
void statistics_ht(hashtable_t* hashtable) {

  printf("Printing hashtable statistics\n");
  printf("Load limits: %.0f%% min / %.0f%% max\n", (100 * hashtable->min_load_factor), (100 * hashtable->max_load_factor));
  printf("Buckets: %d used / %d total (%.0f%% current load)\n", hashtable->num_buckets, hashtable->size, 100 * (double) ((double) hashtable->num_buckets / hashtable->size));
}

// show snapshot of hashtable
void snapshot_ht(hashtable_t* hashtable) {

  int i, j;
  int size = hashtable->size;

  printf("Printing hashtable snapshot\n");
  printf("[entry #] (first key, first value) --> ... --> (last key, last value)\n");
  printf("-----------------------------------------------------------\n");

  bucket_t* current_bucket;
  for(i=0;i<size;i++) {
    current_bucket = (bucket_t*) hashtable->entries[i];
    printf("[entry %d] ", i);
    while(current_bucket != NULL) {
      printf("(%s, %s) --> ", current_bucket->key, current_bucket->value);
      current_bucket = (bucket_t*) current_bucket->next;
    }
    printf("null\n");
  }
}

// AUXILIARY FUNCTIONS DEFINITIONS

// create new bucket
bucket_t* create_bucket(char *key, char *value) {

  // allocate new bucket and set values
  bucket_t* new_bucket = malloc(sizeof(bucket_t));
  new_bucket->key = strdup(key);
  new_bucket->value = strdup(value);
  new_bucket->next = NULL;
  return new_bucket;
}

// deallocate all entries and free used space
int deallocate_all_entries(bucket_t** entries, int size) {

  int i, freed_buckets = 0;
  // for each hashtable entry
  for(i=0;i<size;i++) {
    bucket_t* bucket = entries[i];
    // free all entries
    freed_buckets += delete_buckets(bucket);
  }
  // free list of entries
  free(entries);

  return freed_buckets;
}

// deallocates the space used by a buckets and all those linked to it
int delete_buckets(bucket_t* bucket) {

  int freed_buckets = 0;

  // check if bucket is empty
  if(bucket != NULL) {    
    bucket_t* current_bucket = bucket;
    // traverse all buckets and free them
    while(current_bucket!=NULL) {
      // save next bucket
      bucket_t* next = (bucket_t *) current_bucket->next;
      // free current bucket
      free(current_bucket->key);
      free(current_bucket->value);
      free(current_bucket);
      freed_buckets++;
      // place next bucket on top
      current_bucket = next;
    }
  }
  return freed_buckets;
}

/* // check if key exists */
/* bool check_key(hashtable_t *hashtable, char *key) { */

/*   bool enable_feedback = hashtable->enable_feedback; */
/*   // temporarily disable feedback */
/*   hashtable->enable_feedback = false; */
  
/*   // get value for key */
/*   char *value = retrieve_ht(hashtable, key); */

/*   // restore feedback */
/*   hashtable->enable_feedback = enable_feedback; */
  
/*   if (value == NULL) return false; */
/*   return true; */
/* } */

// HASH FUNCTIONS DEFINITIONS

uint32_t jenkins_one_at_a_time_hash(char *key, size_t len) {
  uint32_t hash, i;
  for(hash = i = 0; i < len; ++i) {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}
