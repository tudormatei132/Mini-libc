// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	
  void *start = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  // if we encounter any errors, return NULL
  if (start == MAP_FAILED) {
    return NULL;
  }
  int ans = mem_list_add(start, size);
  if (ans == -1) {
    // free the memory 
    munmap(start, size);
    return NULL;
  }

	return start;
}

void *calloc(size_t nmemb, size_t size)
{
	// the same as malloc, but we memset the memory to 0
  void *start = mmap(NULL, size * nmemb, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (start == MAP_FAILED) {
    return NULL;
  }
  int ans = mem_list_add(start, nmemb * size);
  if (ans == -1)
    return NULL;
  memset(start, 0, nmemb * size);
	return start;
}

void free(void *ptr)
{

  if (!ptr)
    return;
  // find the pointer in the list so we can
  // get how much memory was allocated
  struct mem_list* temp = mem_list_find(ptr);
  if (!temp) {
    return;
  }

  int res = munmap(ptr, temp->len);
  if (res == -1)
    return;
  // remove it from the list
  mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
  void *result = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (result == MAP_FAILED)
    return NULL;
  // find ptr in the list
  struct mem_list *item = mem_list_find(ptr);
  // use memmove to copy the data
  memmove(result, ptr, item->len);
  // then free the old memory
  free(ptr);
	return result;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *result = mmap(NULL, size * nmemb, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (result == MAP_FAILED)
    return NULL;
  struct mem_list *item = mem_list_find(ptr);

  memmove(result, ptr, item->len);
  free(ptr);
	return result;
}
