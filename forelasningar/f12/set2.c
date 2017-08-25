#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// The element type in the array
#define chunk_type_t uint64_t
// How many bits in an element
#define Bits (sizeof(chunk_type_t) * 8)

// Creates a bit mask
// Bit_mask(3) = ...00001000 
#define Bit_mask(bit) (1UL << (bit))

// Calculate the number of chunks in the element array
#define Chunk(element) (element / Bits)
#define Chunks(elements) (Chunk(elements) + ((elements % Bits) ? 1 : 0))

struct set
{
  size_t size;
  chunk_type_t elements[]; /// Fancy C99-trick, avoids two allocations
};

/// Should move to set.h ////////////////////////////////////
typedef struct set set_t;

set_t *set_new(int size);
size_t set_size(set_t *s);
void set_add(set_t *s, int element);
void set_remove(set_t *s, int element);
bool set_has(set_t *s, int element);
void set_free(set_t *s);
// more functions should be added here
/// end of set.h

/// Create a new set with support for elements [0,size-1]
/// (Note the trick with only using one allocation)
set_t *set_new(int size)
{
  /// Calculate the size of set set + array
  set_t *s = calloc(1, sizeof(set_t) + Chunks(size) * sizeof(chunk_type_t));
  s->size = size;
  return s;
}

/// Accessor for the size of a set
size_t set_size(set_t *const s)
{
  return s->size;
}

/// Private function. First implementation attempt of set_members.
static inline size_t set_members1(set_t *const s)
{
  size_t sum = 0;

  int chunks = set_size(s) / sizeof(unsigned int) / 8;
  unsigned int *elements = (unsigned int *)s->elements;
  /// Optimisation: uses a gcc-specific function for counting set bits 
  for (int i = 0; i < chunks; ++i)
    sum += __builtin_popcount(elements[i]); 

  return sum;
}

/// Private function. Second implementation attempt of set_members.
static inline size_t set_members2(set_t *const s)
{
  size_t sum = 0;

  /// Is this good code?
  size_t size = set_size(s);
  for (int i = 0; i < size; ++i)
    if (set_has(s, i))
      sum += 1;

  return sum;
}

/// Returns the count of members in a set
size_t set_members(set_t *const s)
{
  /// Delegates to one of the actual implementations, change to see the differnce in your profiling
  return set_members2(s);
}

/// Internal function for calculating the number of chunks in a set
static inline int set_chunks(set_t *const s)
{
  return Chunks(s->size);
}

/// Add element to the set
void set_add(set_t *s, int element)
{
  s->elements[element / Bits] |= Bit_mask(element % Bits);
}

/// Remove element from the set
void set_remove(set_t *s, int element)
{
  s->elements[element / Bits] &= ~Bit_mask(element % Bits);
}

/// Test if element is in the set
bool set_has(set_t *const s, int element)
{
  return s->elements[element / Bits] & (1UL << (element % Bits));
}

/// Return a new set with the intersection of two sets a and b
set_t *set_intersection(set_t *const a, set_t *const b)
{
  assert(set_size(a) == set_size(b)); 

  set_t *result = set_new(set_size(a));
  
  const int chunks = set_chunks(a);
  for (int i = 0; i < chunks; ++i)
    {
      result->elements[i] = 
        a->elements[i] &
        b->elements[i]; 
    }

  return result;
}

/// Return a new set with the union of two sets a and b
/// Implementation 1
static set_t *set_union1(set_t *const a, set_t *const b)
{
  assert(set_size(a) == set_size(b)); 

  int size = set_size(a);
  set_t *result = set_new(size);

  for (int i = 0; i < size; ++i)
    {
      if (set_has(a, i) || set_has(b, i)) set_add(result, i);
    }

  return result;
}

/// Return a new set with the union of two sets a and b
/// Implementation 2
static set_t *set_union2(set_t *const a, set_t *const b)
{
  assert(set_size(a) == set_size(b)); 

  set_t *result = set_new(set_size(a));

  const int chunks = set_chunks(a);
  for (int i = 0; i < chunks; ++i)
    {
      result->elements[i] =
        a->elements[i] |
        b->elements[i];
    }

  return result;
}

/// Return a new set with the union of two sets a and b
/// Delegates to set_union1 or set_union2
set_t *set_union(set_t *const a, set_t *const b)
{
  return set_union1(a, b);
}

/// Return a new set with all elements of a except those also in b
set_t *set_subtraction(set_t *const a, set_t *const b)
{
  assert(set_size(a) == set_size(b)); 

  set_t *result = set_new(set_size(a));

  int chunks = set_chunks(a);
  for (int i = 0; i < chunks; ++i)
    {
      result->elements[i] =
         a->elements[i] &
        ~b->elements[i];
    }
  
  return result;
}

/// Free a set
void set_delete(set_t *s)
{
  free(s);
}

/// Debug for printing a set 
void set_print(set_t *const s)
{
  bool sep = false;
  printf("{ ");
  
  for (int i = 0; i < set_size(s); ++i)
    if (set_has(s, i))
      {
        if (sep) printf(", ");
        printf("%d", i);
        sep = true;
      }

  printf(" }\n");
}

// Not part of the bitset, used for the main function /////////////////////////////////////////////

#define coin_flip() (rand() % 2)

#define Size (16 * 1024 * 1024)

/// Stupid program that can be used to do some minimal profiling
int main(void)
{
  set_t *a = set_new(Size);
  set_t *b = set_new(Size);

  for (int i = 0; i < Size; ++i)
    if (coin_flip())
      set_add(a, i);

  for (int i = 0; i < Size; ++i)
    if (coin_flip())
      set_add(b, i);

  set_t *c = set_union(a, b);

  set_t *d = set_subtraction(a, a);

  set_t *e = set_intersection(c, c);

  printf("a: %zd\n", set_members(a));
  printf("b: %zd\n", set_members(b));
  printf("c: %zd\n", set_members(c));
  printf("d: %zd\n", set_members(d));
  printf("e: %zd\n", set_members(e));

  set_delete(a);
  set_delete(b);
  set_delete(c);
  set_delete(d);
  set_delete(e);
  
  return 0;
}
