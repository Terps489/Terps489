flags = -Wall -Wextra -Werror
name = -o ../build
files = state_sort.o
make: clear clean state_sort state_search clear_state
open: 
	../build/graph
clear:
	clear
clean:
	rm -rf *.o $(name)/Quest_1
state_sort: QUEST_1.o
	gcc $(flags) $(files) $(name)/Quest_1
	rm -rf *.o
state_search: QUEST_2.o
	gcc $(flags) $(files) $(name)/Quest_2
	rm -rf *.o
clear_state: QUEST_3.o
	gcc $(flags) $(files) $(name)/Quest_3
	rm -rf *.o
QUEST_1.o:
	gcc $(flags) -c -DQUEST_1 state_sort.c
QUEST_2.o:
	gcc $(flags) -c -DQUEST_2 state_sort.c
QUEST_3.o:
	gcc $(flags) -c -DQUEST_3 state_sort.c
check:
	clang-format -i *.c
	cppcheck —enable=all —suppress=missingIncludeSystem *.c
	leaks -atExit -- ../build/Quest_1
push:
	git switch develop
	rm -rf *.o
	cp ../materials/linters/.clang-format .
	clang-format -i *.h *.c
	git add .
	git commit -m "pushed with make"
	git push origin develop