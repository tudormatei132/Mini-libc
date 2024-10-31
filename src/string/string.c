// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
  char *d = destination;
  char *s = (char *)source;
  while (*s) {
    *d = *s;
    s++;
    d++;
  }
  *d = 0;
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{	
  char *d = destination;
  char *s = (char *)source;
  while (len && *s) {
    *d = *s;
    s++;
    d++;
    len--;
  }
  // we will add (len - strlen(source)) zeroes at the end of destination
  while (len--) { // if len is greater than the length of source
    *d = 0;
    d++;
  }
	return destination;
}

char *strcat(char *destination, const char *source)
{	
  char *d = destination;
  char *s = (char *)source;
  // find the null character for destination 
  while (*d) {
    d++;
  }
  // this is equivalent to strcpy(d, s)
  while (*s) {
    *d = *s;
    s++;
    d++;
  }
  *d = 0;
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{	
  char *d = destination;
  char *s = (char *)source;
  // find the null character
  while (*d) {
    d++;
  }
  // similar to strncpy, but we do not add any zeroes if len > strlen(source)
  while (len-- && *s) {
    *d = *s;
    d++;
    s++;
  }
  *d = 0;
	return destination;
}

int strcmp(const char *str1, const char *str2)
{ 
  char *s1 = (char *)str1;
  char *s2 = (char *)str2;
  // keep checking if the two strings are the same
  while (*s1 && *s2) {
    // return when we find a difference
    if (*s1 != *s2) {
      return (int)(*s1 - *s2);
    }
    s1++;
    s2++;
  }
  // if strlen(str2) > strlen(str1)
  if (*s2) {
    return -(int)(*s2);
  } else if (*s1) { // if strlen(str1) > strlen(str2)
    return (int)(*s1);
  }
  // we didn't find any different characters and their lengths are the same
	return 0;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
  char *s1 = (char *)str1;
  char *s2 = (char *)str2;
  while (len && *s1 && *s2) {
    if (*s1 != *s2) {
      return (int)(*s1 - *s2);
    }
    s1++;
    s2++;
    len--;
  }
  // if len is greater than 0, it means at least of the strings is shorter
  // than len. If we didn't reach the null character in str2, return a negative
  // value, or a positive value if we did reach it, but didn't do the same with
  // str1.
  if (len) {
    if (*s2) {
      return -(int)(*s2);
    } else {
      return (int)(*s1);
    }
  }
  // return 0 if the first len characters are the same
  // or if the strings are equal if their lengths are
  // lower than len
	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	
  char *s = (char *)str;
  while (*s) {
    if (c == *s)
      return s;
    s++;
  }
	return NULL;
}

char *strrchr(const char *str, int c)
{
	// in result, it will be stored the last appearance of c in str
  char *result = NULL;
  char *s = (char *)str;
  while (*s) {
    if (*s == c)
      result = s;
    s++;
  }
	return result;
}

char *strstr(const char *haystack, const char *needle)
{
	
  char *h = (char *)haystack;
  int len = strlen(needle);
  while (*h) {
    // check if the len-long string that starts at the h location is the same
    // as our needle
    if (!strncmp(h, needle, len))
      return h;
    h++;
  }
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	
  char *h = (char *)haystack;
  char *result = NULL;
  int len = strlen(needle);
  while (*h) {
    if (!strncmp(h, needle, len))
      result = h;
    h++;
  }
	return result;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	// convert our void * to char *, so we can iterate byte by byte

  char *d = (char *)destination;
  char *s = (char *)source;
  // change the first num bytes from the memory address stored in destination
  // so they match the first num bytes from the other address
  while (num--) {
    *d = *s;
    d++;
    s++;
  }
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	// we need to keep in mind that the two memorry addresses
  // might overlap at some point
  char *d = (char *)destination;
  char *s = (char *)source;
  // that's why we need to split our problem in two cases
  // 1. if destination is greater than source
  if (d > s) {
    // we need to start from the end so we get to copy
    // the last bytes before they are changed
    d += num - 1;
    s += num -1;
    while (num--) {
      *d = *s;
      d--;
      s--;
    }
  // 2. if source is greater than destination
  } else {
    // basically a memcpy()
    while (num--) {
      *d = *s;
      d++;
      s++;
    }
  }
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	char *p1 = (char *)ptr1;
  char *p2 = (char *)ptr2;
  // search for differences in the first num bytes
  while (num--) {
    if (*p1 != *p2) {
      // the function returns a value greater than 0 if *p1 > *p2
      // or lowe than 0 otherwise
      return (int)(*p1 - *p2);
    }
    p1++;
    p2++;
  }
  // the values stored in the num bytes match
  return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
  char *s = (char *)source;
  while (num--) {
    *s = (char) value;
    s++;
  }
	return source;
}
