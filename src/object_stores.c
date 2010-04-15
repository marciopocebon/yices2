/*
 * Store for allocation/release of (small) objects of fixed size.
 */

#include <assert.h>

#include "memalloc.h"
#include "object_stores.h"


/*
 * Initialize s: 
 * - objsize = size of all objects in s
 * - n = number of objects per block
 */
void init_objstore(object_store_t *s, uint32_t objsize, uint32_t n) {
  assert(objsize <= MAX_OBJ_SIZE);
  assert(0 < n && n <= MAX_OBJ_PER_BLOCK);

  // round up objsize to a multiple of 8 for pointer alignment
  objsize = (objsize + 7) & ((uint32_t )(~7));

  s->bnk = NULL;
  s->free_list = NULL;
  s->free_index = 0;
  s->objsize = objsize;
  s->blocksize = objsize * n;
}


/*
 * Allocate an object in s
 */
void *objstore_alloc(object_store_t *s) {
  void *tmp;
  uint32_t i;
  object_bank_t *new_bank;

  tmp = s->free_list;
  if (tmp != NULL) {
    // This may be unsafe. Replaced by memcpy.
    //    s->free_list = * ((void **) tmp);
    memcpy(&s->free_list, tmp, sizeof(void*));
    return tmp;
  }

  i = s->free_index;
  if (i == 0) {
    new_bank = (object_bank_t *) safe_malloc(sizeof(object_bank_t) + s->blocksize * sizeof(char));
    new_bank->next = s->bnk;
    s->bnk = new_bank;
    i = s->blocksize;
  }

  assert(i >= s->objsize);

  i -= s->objsize;
  s->free_index = i;
  tmp = s->bnk->block + i;

  return tmp;
}


/*
 * Delete all objects
 */
void delete_objstore(object_store_t *s) {
  object_bank_t *b, *next;

  b = s->bnk;
  while (b != NULL) {
    next = b->next;
    safe_free(b);
    b = next;
  }

  s->bnk = NULL;
  s->free_list = NULL;
  s->free_index = 0;
}


/*
 * Apply finalizer f to all objects then delete s
 */
void objstore_delete_finalize(object_store_t *s, void (*f)(void *)) {
  object_bank_t *b, *next;
  void *obj;
  uint32_t k, i;

  b = s->bnk;
  k = s->free_index;
  while (b != NULL) {
    next = b->next;
    for (i=k; i<s->blocksize; i += s->objsize) {
      obj = (void *) (b->block + i);
      f(obj);      
    }
    safe_free(b);
    k = 0;
    b = next;
  }

  s->bnk = NULL;
  s->free_list = NULL;
  s->free_index = 0;
}


/*
 * Reset store s: remove all objects
 * - keep only one bank
 */
void reset_objstore(object_store_t *s) {
  object_bank_t *b, *next;

  b = s->bnk;
  if (b != NULL) {
    next = b->next;
    while (next != NULL) {
      safe_free(b);
      b = next;
      next = b->next;
    }
  }

  s->bnk = b;
  s->free_list = NULL;
  s->free_index = 0;
}
