flags = -Wall -Wextra -Werror
quest = ../build/
all: check door_struct list_test stack_test
door_struct:
	gcc $(flags) dmanager_module.c -o $(quest)Quest_1
list_test:
	gcc $(flags) list_test.c list.c -o $(quest)Quest_2
stack_test:
	gcc $(flags) stack_test.c list.c stack.c -o $(quest)Quest_3
clean:
	rm -rf *.o $(quest)Quest_1 $(quest)Quest_2 $(quest)Quest_3
rebuild: clean all

check: 
	cppcheck —enable=all —suppress=missingIncludeSystem *.c
	clang-format -i *.c *.h
