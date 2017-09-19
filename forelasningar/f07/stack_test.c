#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include "stack.h"

void test_stack_creation()
{
  stack_t *stack = stack_new();
  CU_ASSERT_TRUE(stack_size(stack) == 0);
  stack_delete(stack);
}

void test_stack_height()
{
  stack_t *stack = stack_new();

  for (int i = 0; i < 10; ++i) stack_push(stack, NULL);
  CU_ASSERT_TRUE(stack_size(stack) == 10);

  for (int i = 0; i < 10; ++i) stack_push(stack, NULL);
  CU_ASSERT_TRUE(stack_size(stack) == 20);

  stack_pop(stack);
  CU_ASSERT_TRUE(stack_size(stack) == 19);

  stack_push(stack, NULL);
  CU_ASSERT_TRUE(stack_size(stack) == 20);

  stack_pop(stack);
  stack_pop(stack);
  CU_ASSERT_TRUE(stack_size(stack) == 17);
  
  stack_delete(stack);
}

void test_stack_push_pop()
{
  /// TODO
  stack_t *s = stack_new();
  for (int i = 0; i < 1000000; ++i)
    {
      stack_push(s, NULL);
      CU_TEST(stack_size(s) == i + 1);
    }

}

void test_stack_top()
{
  /// TODO
}

int main(int argc, char *argv[argc])
{
  // Initialise
  CU_initialize_registry();

  // Set up suites and tests
  CU_pSuite creation = CU_add_suite("Test creation and height", NULL, NULL);
  CU_add_test(creation, "Creation", test_stack_creation);
  CU_add_test(creation, "Height", test_stack_height);

  CU_pSuite pushpoptop = CU_add_suite("Test push, pop and top", NULL, NULL);
  CU_add_test(pushpoptop, "Push and pop", test_stack_push_pop);
  CU_add_test(pushpoptop, "Top", test_stack_top);
 
  // Actually run tests
  CU_basic_run_tests();
  
  // Tear down
  CU_cleanup_registry();
  return CU_get_error();
}

