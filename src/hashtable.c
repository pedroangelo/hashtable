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

// MACROS

// GLOBAL VARIABLES

// MAIN FUNCTIONS DEFINITIONS

// create a empty hashtable and return the address
hashtable_t *create_ht(int size) {

	int i;
	// allocate space for the hashtable
	hashtable_t *hashtable = malloc(sizeof(hashtable_t));
	// set hashtable size
	hashtable->size = size;
	// create array of buckets
	hashtable->entries = malloc(size * sizeof(entry_t));

	entry_t current_entry;
	// initialize entries
	for(i=0;i<size;i++) {
		current_entry = hashtable->entries[i];
		current_entry.size = 0;
		current_entry.first_bucket = NULL;
		current_entry.last_bucket = NULL;
	}
	return hashtable;
}

// collect statistics from hashtable
void statistics_ht(hashtable_t *hashtable) {

	int i;
	int used_entries = 0;
	int num_buckets = 0;
	int size = hashtable->size;

	printf("\n### HASHTABLE ENTRIES ###\n\n");
	printf("SIZE: %d ENTRIES\n", size);

	entry_t entry;
	int entry_size;
	for(i=0;i<size;i++) {
		entry = hashtable->entries[i];
		entry_size = entry.size;
		printf("ENTRY %d: %d BUCKETS\n", i, entry_size);
		num_buckets += entry_size;
		if(entry_size != 0) used_entries++;
	}
	printf("\n### HASHTABLE STATISTICS ###\n");
	printf("USED %d ENTRIES\n", used_entries);
	printf("USED %d BUCKETS\n", num_buckets);
}

// show snapshot of hashtable
void snapshot_ht(hashtable_t *hashtable) {

	int i, j;
	int size = hashtable->size;

	printf("\n### HASHTABLE SNAPSHOT ###\n\n");

	entry_t *entry;
	bucket_t *bucket;
	int entry_size;
	for(i=0;i<size;i++) {
		entry = (entry_t *) &hashtable->entries[i];
		entry_size = entry->size;
		bucket = (bucket_t *) entry->first_bucket;
		printf("[ENTRY %d] :: ", i);
		if(entry_size != 0) {
			printf("FIRST (%s, %s) | ", entry->first_bucket->key, entry->first_bucket->value);
			printf("LAST (%s, %s) | ", entry->last_bucket->key, entry->last_bucket->value);
		} else {
			printf("FIRST (NULL, NULL) | ");
			printf("LAST (NULL, NULL) | ");
		}
		for(j=0; j<entry_size;j++) {
			if(j!=0) bucket = (bucket_t *) bucket->next;
			printf("(%s, %s) -> ", bucket->key, bucket->value);
		}
		printf("NULL\n");
	}
}

// deallocates the space used by the hash table
void delete_ht(hashtable_t *hashtable) {

	int i, freed_buckets = 0;
	// get size of hashtable
	int size = hashtable->size;
	// for each hashtable entry
	for(i=0;i<size;i++) {
		// free all entries
		freed_buckets += delete_entry(&hashtable->entries[i]);
	}
	// free list of entries
	free(hashtable->entries);
	// free hashtable
	free(hashtable);

	//printf("\n### DELETING HASHTABLE ###\n");
	//printf("USED BUCKETS FREED: %d\n", freed_buckets);
}

// insert (key, value) pair in hash
void insert_ht(hashtable_t *hashtable, char *key, char *value) {

	// get new bucket
	bucket_t *new_bucket = create_bucket(key, value);
	// get hash value of key
	uint32_t hash = jenkins_one_at_a_time_hash(key, strlen(key));
	// get index from hash
	int index = hash % hashtable->size;
	// get entry in index position
	entry_t *entry = &hashtable->entries[index];
	// if there is no bucket in entry
	if(entry->size == 0) {
		entry->first_bucket = new_bucket;
		entry->last_bucket = new_bucket;

	// if there is a collision
	} else {
		// get last bucket
		bucket_t *last = entry->last_bucket;
		// point last bucket's next to new_bucket
		last->next = (struct bucket_t *) new_bucket;
		// point entry's last bucket to new bucket
		entry->last_bucket = new_bucket;
	}
	// increment counter
	entry->size++;
}

// retrieve value given the key
char *retrieve_ht(hashtable_t *hashtable, char *key) {
	// get hash value of key
	uint32_t hash = jenkins_one_at_a_time_hash(key, strlen(key));
	// get index from hash
	int i, index = hash % hashtable->size;
	// get entry in index position
	entry_t *entry = &hashtable->entries[index];
	// get first bucket
	bucket_t *current_bucket = entry->first_bucket;
	// search for key
	for(i=0;i<entry->size;i++) {
		// if keys match, return value
		if(strcmp(current_bucket->key, key) == 0) return current_bucket->value;
		// place next bucket in current_bucket
		current_bucket = (bucket_t *) current_bucket->next;
	}
	return NULL;
}

// remove value given the key and return it
char *remove_ht(hashtable_t *hashtable, char *key) {
	// get hash value of key
	uint32_t hash = jenkins_one_at_a_time_hash(key, strlen(key));
	// get index from hash
	int i, index = hash % hashtable->size;
	// get entry in index position
	entry_t *entry = &hashtable->entries[index];
	// get first bucket
	bucket_t *current_bucket = entry->first_bucket;
	// variable that holds previous bucket
	bucket_t *previous_bucket = entry->first_bucket;
	// search for key
	for(i=0;i<entry->size;i++) {
		// if keys match
		if(strcmp(current_bucket->key, key) == 0) {
			// store value
			char* value = current_bucket->value;

			// update entry pointers and next bucket pointer

			// entry only has one bucket
			if(entry->size == 1) {
				entry->first_bucket = NULL;
				entry->last_bucket = NULL;
			}

			// entry has more than one bucket
			else {
				// removing first bucket, set first bucket to next bucket
				if(i == 0) entry->first_bucket = (bucket_t *) current_bucket->next;
				// removing last bucket
				if(i == entry->size-1) {
					entry->last_bucket = (bucket_t *) previous_bucket;
					previous_bucket->next = NULL;
				}
				// removing bucket that isn't first or last bucket, , update pointer to next bucket
				if(i != 0 && i != entry->size-1) previous_bucket->next = current_bucket->next;
			}

			// free current bucket
			free(current_bucket);
			// decrement counter
			entry->size--;
			// return value;
			return value;
		}
		// place next bucket in current_bucket
		current_bucket = (bucket_t *) current_bucket->next;
		if(i!=0) previous_bucket = (bucket_t *) previous_bucket->next;
	}
	return NULL;
}

// AUXILIARY FUNCTIONS DEFINITIONS

// deallocates the space used by a entry and free all bucket under that entry
int delete_entry(entry_t *entry) {

	int i, num_buckets = entry->size;
	int freed_buckets = 0;
	// check if entry is empty
	if(num_buckets != 0) {

		bucket_t *current_bucket = entry->first_bucket;
		// traverse all buckets and free them
		for(i=0;i<num_buckets;i++) {
			// save next bucket
			bucket_t *next = (bucket_t *) current_bucket->next;
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

// create new bucket
bucket_t *create_bucket(char *key, char *value) {

	// allocate new bucket and set values
	bucket_t *new_bucket = malloc(sizeof(bucket_t));
	new_bucket->key = strdup(key);
	new_bucket->value = strdup(value);
	new_bucket->next = NULL;
	return new_bucket;
}

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
