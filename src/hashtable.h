// INCLUDES

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// STRUCTURES

// hashtable bucket holds:
// - key: the key
// - value: the value the key associates to
// - next: pointer to next bucket
typedef struct _bucket_t {
  char* key;
  char* value;
  struct bucket_t* next;
} bucket_t;

// hashtable representation contains:
// - size: size of hashtable, i.e. size of array entries
// - num_buckets: number of current allocated buckets
// - min_load_factor: threshold at which hashtable size is halved
// - max_load_factor: threshold at which hashtable size is doubled
// - enable_feedback: toggle between true and false to print status messages or not
// - entries: array of pointers to buckets
typedef struct _hashtable_t {
  int size;
  int num_buckets;
  float min_load_factor;
  float max_load_factor;
  bool enable_feedback;
  bucket_t** entries;
} hashtable_t;

// MAIN FUNCTIONS DECLARATIONS
hashtable_t* ht_create(int size, float min_load_factor, float max_load_factor, bool enable_feedback);
void ht_delete(hashtable_t* hashtable);
void ht_insert(hashtable_t* hashtable, char* key, char* value);
char* ht_remove(hashtable_t* hashtable, char* key);
void ht_resize(hashtable_t* hashtable, int size);
char* ht_retrieve(hashtable_t* hashtable, char* key);

// INFORMATIVE FUNCTIONS DECLARATIONS
void ht_snapshot(hashtable_t* hashtable);
void ht_statistics(hashtable_t* hashtable);

// AUXILIARY FUNCTIONS DECLARATIONS
static int calculate_index(hashtable_t* hashtable, char* key);
static bool check_key(hashtable_t* hashtable, char* key);
static bucket_t* create_bucket(char* key, char* value);
static int deallocate_all_entries(bucket_t** entries, int size);
static int deallocate_buckets(bucket_t* buckets);

// HASH FUNCTIONS DECLARATIONS
static uint32_t jenkins_one_at_a_time_hash(char* key, size_t len);
