# Compile stack_test to an executable
stack_test:
	gcc -ggdb --coverage -Wall -pedantic stack.c stack_test.c -o stack_test -lcunit

# Run the tests (dependency: compilation)
test:	stack_test
	./stack_test

# Print test coverage (dependency: run tests and thus also compilation)
coverage: test
	gcov --all-blocks --branch-probabilities --branch-counts --display-progress stack.c
	@echo NOTE: You can open stack.c.gcov in e.g. emacs for more details. 

# Remove temporary files 
clean:
	rm -f stack_test stack.gcda stack.gcno stack_test.gcda stack_test.gcno stack.c.gcov  
