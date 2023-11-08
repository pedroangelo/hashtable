// INCLUDES
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// STRUCTURES

// hashtable bucket:
// - holds the key value pair
// - holds pointer to next bucket
typedef struct _bucket_t {
	char *key;
	char *value;
	struct bucket_t *next;
} bucket_t;

// hashtable entry:
// - size: holds the number of buckets
// - first_bucket: holds pointer to first bucket
// - last_bucket: holds pointer to last bucket
typedef struct _entry_t {
	int size;
	bucket_t *first_bucket;
	bucket_t *last_bucket;
} entry_t;

// hashtable representation contains:
// - size: size of hashtable
// - num_buckets: number of allocated buckets
// - min_load_factor: threshold at which hashtable size is halved
// - max_load_factor: threshold at which hashtable size is doubled
// - entries: pointer to list of entries
typedef struct _hashtable_t {
	int size;
	int num_buckets;
	float min_load_factor;
  float max_load_factor;
	entry_t *entries;
} hashtable_t;

// MAIN FUNCTIONS DECLARATIONS
hashtable_t* create_ht(int size, float min_load_factor, float max_load_factor);
void statistics_ht(hashtable_t *hashtable);
void snapshot_ht(hashtable_t *hashtable);
void delete_ht(hashtable_t *hashtable);
void insert_ht(hashtable_t *hashtable, char *key, char *value);
char* retrieve_ht(hashtable_t *hashtable, char *key);
char* remove_ht(hashtable_t *hashtable, char *key);
void resize_ht(hashtable_t *hashtable, int size);

// AUXILIARY FUNCTIONS DECLARATIONS
static int delete_entry(entry_t *entry);
static bucket_t* create_bucket(char *key, char *value);
static bool check_key(hashtable_t *hashtable, char *key);
static void	deallocate_entries(entry_t *entries, int size);

// HASH FUNCTIONS DECLARATIONS
static uint32_t jenkins_one_at_a_time_hash(char *key, size_t len);
