#ifndef __common_h__
#define __common_h__

/// Functions for handling genericity
typedef elem_t(*element_copy_fun)(elem_t);
typedef void(*element_free_fun)(elem_t);
typedef size_t(*element_comp_fun)(elem_t, elem_t);
typedef bool(*elem_apply_fun)(elem_t elem, void *data);

typedef union element elem_t;

/// Element wrapper
///
/// Elements in the list are stored inside an elem_t which is
/// passed in by copy. 
///
union element
{
  int   i; 
  uint  u;
  void *p; 
  float f;
};

#endif
