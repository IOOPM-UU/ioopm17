#include <string.h>
#include "CUnit/Basic.h"

#include "list.h"
#include "bst.h"
#include "nextword.h"

static FILE* temp_file = NULL;

int init_suite_bst(void)
{
  return 0;
}

int clean_suite_bst(void)
{
  return 0;
}

int init_suite_list(void)
{
  return 0;
}

int clean_suite_list(void)
{
  return 0;
}

int init_suite_nw(void)
{
  if (NULL == (temp_file = fopen("temp.txt", "w+")))
    {
      return -1;
    }
  else
    {
      return 0;
    }
}

int clean_suite_nw(void)
{
  if (0 != fclose(temp_file))
    {
      return -1;
    }
  else
    {
      temp_file = NULL;
      return 0;
    }
}

void testBST_INSERT(void)
{
  TreeLink t = insert(NULL, "spam\0", 1);
  CU_ASSERT(strcmp(t->key, "spam\0") == 0);
  CU_ASSERT(t != NULL);
  CU_ASSERT(t->left == NULL);
  CU_ASSERT(t->right == NULL);
  CU_ASSERT(t->rowlist != NULL);
  CU_ASSERT(listlength(t->rowlist) == 1);
  t = insert(t, "spam\0", 2);
  CU_ASSERT(listlength(t->rowlist) == 2);

  TreeLink d = insert(NULL, "ni\0", 1);
  d = insert(d, "spam\0", 2);
  d = insert(d, "eki\0", 3);
  CU_ASSERT(strcmp(d->key, "ni\0") == 0);
  CU_ASSERT(strcmp(d->right->key, "spam\0") == 0);
  CU_ASSERT(strcmp(d->left->key, "eki\0") == 0);
}

void testBST_REMOVE(void)
{
  /* Note that this test is not run automatically, modifications
     further down are necessary */
}

void testBST_DEPTH(void)
{
  TreeLink t = insert(NULL, "ni\0", 1);
  CU_ASSERT(depth(t) == 1);
  t = insert(t, "spam\0", 2);
  CU_ASSERT(depth(t) == 2);
  t = insert(t, "eki\0", 3);
  CU_ASSERT(depth(t) == 2);
  t = insert(t, "eki\0", 4);
  CU_ASSERT(depth(t) == 2);
  CU_ASSERT(strcmp(t->left->key, "eki\0") == 0);
}

void testBST_SIZE(void)
{
  TreeLink t = insert(NULL, "ni\0", 1);
  CU_ASSERT(size(t) == 1);
  t = insert(t, "spam\0", 2);
  CU_ASSERT(size(t) == 2);
  t = insert(t, "eki\0", 3);
  CU_ASSERT(size(t) == 3);
  t = insert(t, "eki\0", 4);
  CU_ASSERT(size(t) == 3);
}

void testLIST_LISTINSERT(void)
{
  ListLink l = listinsert(1, NULL);
  for (int i=2; i<=10; i++)
    {
      l = listinsert(i, l);
    }

  for (int i=1; i<=10; i++)
    {
      CU_ASSERT(l->value == i);
      l = l->next;
    }
}

void testLIST_LISTLENGTH(void)
{
  ListLink l = listinsert(1, NULL);
  CU_ASSERT(listlength(l) == 1);
  for (int i=2; i<=20; i++)
    {
      l = listinsert(i, l);
      CU_ASSERT(listlength(l) == i);
    }
}

void testNEXTWORD(void)
{
  char buffer[20];
  CU_ASSERT(temp_file != NULL)  // Internal error
  fprintf(temp_file, "spam spam\nbacon spam");
  rewind(temp_file);

  // Läser in nästa ord i strömen "fp". Returnerar 0 vid EOF och 2 vid
  // radbrytning, annars 1.

  int i = nextWord(buffer, temp_file);
  CU_ASSERT(strcmp(buffer, "spam\0") == 0)
  CU_ASSERT(i == 1)
  i = nextWord(buffer, temp_file);
  CU_ASSERT(strcmp(buffer, "spam\0") == 0)
  CU_ASSERT(i == 1)
  i = nextWord(buffer, temp_file);
  CU_ASSERT(i == 2)
  i = nextWord(buffer, temp_file);
  CU_ASSERT(strcmp(buffer, "bacon\0") == 0)
  CU_ASSERT(i == 1)
  i = nextWord(buffer, temp_file);
  CU_ASSERT(strcmp(buffer, "spam\0") == 0)
  CU_ASSERT(i == 1)
  i = nextWord(buffer, temp_file);
  CU_ASSERT(i == 0)
}

int main()
{
  CU_pSuite pSuiteBst = NULL;
  CU_pSuite pSuiteList = NULL;
  CU_pSuite pSuiteNW = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuiteNW = CU_add_suite("nextWord Suite", init_suite_nw, clean_suite_nw);
  if (NULL == pSuiteNW)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  pSuiteList = CU_add_suite("Linked List Suite", init_suite_list, clean_suite_list);
  if (NULL == pSuiteList)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  pSuiteBst = CU_add_suite("Binary Search Tree Suite", init_suite_bst, clean_suite_bst);
  if (NULL == pSuiteBst)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
    (NULL == CU_add_test(pSuiteBst, "test of insert()", testBST_INSERT)) ||
    (NULL == CU_add_test(pSuiteBst, "test of size()", testBST_SIZE)) ||
    (NULL == CU_add_test(pSuiteBst, "test of depth()", testBST_DEPTH))
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
    (NULL == CU_add_test(pSuiteList, "test of listinsert()", testLIST_LISTINSERT)) ||
    (NULL == CU_add_test(pSuiteList, "test of listlength()", testLIST_LISTLENGTH))
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
    (NULL == CU_add_test(pSuiteNW, "test of nextWord()", testNEXTWORD))
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

